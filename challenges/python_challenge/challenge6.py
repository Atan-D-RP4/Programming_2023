import zipfile, re

file = zipfile.ZipFile('channel.zip')
num = '90052'

comment = ''
while True:
    content = file.read(num + '.txt').decode('utf-8')
    print(content)
    comment = comment + file.getinfo(num + '.txt').comment.decode('utf-8')
    match = re.search(r'Next nothing is (\d+)', content)
    if match:
        num = match.group(1)
    else:
        break

print(comment)
