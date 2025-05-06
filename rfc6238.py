import requests
import hmac
import hashlib
import time
import struct
import base64


def generate_totp(userid, time_step=30, key_suffix="examplesufix"):
    # Step 1: Prepare the shared secret by concatenating userid and key_suffix
    shared_secret = userid + key_suffix

    # Step 2: Get the current Unix timestamp
    timestamp = int(time.time())

    # Step 3: Divide the timestamp by the time step (30 seconds)
    time_counter = timestamp // time_step

    # Step 4: Create the HMAC-SHA-512 hash using the shared secret and time_counter
    key = shared_secret.encode("utf-8")  # Shared secret in bytes
    message = struct.pack(
        ">Q", time_counter
    )  # Convert time_counter to 8 bytes (big-endian)
    hmac_sha512 = hmac.new(key, message, hashlib.sha512).digest()

    # Step 5: Extract the OTP from the HMAC hash
    # We need to get a 10-digit OTP (adjusted to 10 digits by truncation)
    offset = hmac_sha512[-1] & 0x0F  # The offset is the last 4 bits of the hash
    otp = (
        struct.unpack(">I", hmac_sha512[offset : offset + 4])[0] & 0x7FFFFFFF
    )  # Get 4 bytes and truncate
    otp = otp % 10000000000  # Ensure it's a 10-digit OTP

    return f"{otp:010d}"  # Format to 10 digits


def generate_authorization_header(userid):
    # Generate TOTP for the userid
    key_suffix = "HENNGECHALLENGE004"
    totp = generate_totp(userid, key_suffix=key_suffix)

    # Create the Basic Auth credentials string (userid:totp_password)
    credentials = f"{userid}:{totp}"

    # Base64 encode the credentials
    base64_credentials = base64.b64encode(credentials.encode("utf-8")).decode("utf-8")

    # Return the final Authorization header value
    return f"Basic {base64_credentials}"


# Example usage
userid = "chaitanyarp4@gmail.com"
authorization_header = generate_authorization_header(userid)
print("Authorization Header:", authorization_header)

# Define the URL and headers
url = "https://api.challenge.hennge.com/challenges/backend-recursion/004"

# Define the data payload
data = {
    "github_url": "https://gist.github.com/Atan-D-RP4/a0f49be4a4890f4b42fc0e8dc60d6cb8",
    "contact_email": userid,
    "solution_language": "python",
}

headers = {
    "Authorization": authorization_header,
    "Accept": "*/*",
    "Content-Type": "application/json",
    "Content-Length": str(len(str(data))),
}

# Send the POST request
response = requests.post(url, headers=headers, json=data)

# Print the response
print("Status Code:", response.status_code)
print("Response Body:", response.text)
