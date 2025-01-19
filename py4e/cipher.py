def decrypt_caesar(string, shift):
    decrypted = ""
    for char in string:
        if char.isalpha():
            ascii_offset = 65 if char.isupper() else 97
            decrypted += chr((ord(char) - ascii_offset - shift) % 26 + ascii_offset)
        else:
            decrypted += char
    return decrypted
