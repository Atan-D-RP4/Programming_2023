from urllib.request import urlopen
from io import BytesIO
from PIL import Image
import re

url = "http://www.pythonchallenge.com/pc/def/oxygen.png"
image = urlopen(url).read()

image = Image.open(BytesIO(image))

row = [image.getpixel((x, image.height / 2)) for x in range(image.width)]
for i in range(len(row)):
    print(row[i])
string = ""
for i in range(0, len(row), 7):
    string = string + chr(row[i][0])

print(string)
nums = re.findall("\d+", string)
print(nums)

result = map(chr, map(int, nums))
print("".join(result))
