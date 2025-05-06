from urllib.request import urlopen
import re
import bz2
import base64

# Fetch the data from the URL
url = "http://www.pythonchallenge.com/pc/def/integrity.html"
data = urlopen(url).read().decode()

# Extract the comment block containing the username and password
comment = re.findall(r'<!--(.*?)-->', data, re.DOTALL)[0]

un = re.findall(r'un: \'(.*?)\'', comment)[0]
pw = re.findall(r'pw: \'(.*?)\'', comment)[0]

# encode the username and password into a bytes object
un_bytes = un.encode()
pw_bytes = pw.encode()

print("Username (base64):", un)
print("Password (base64):", pw)

# Does not work for some reason that is beyond me
# Decompress the username and password
un_decompressed = bz2.decompress(un_bytes).decode()
pw_decompressed = bz2.decompress(pw_bytes).decode()

print("Username:", un_decompressed)
print("Password:", pw_decompressed)

