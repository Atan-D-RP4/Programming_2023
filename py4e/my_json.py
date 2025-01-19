import json
from urllib.request import urlopen
from bs4 import BeautifulSoup
import ssl

# Ignore SSL certificate errors
ctx = ssl.create_default_context()
ctx.check_hostname = False
ctx.verify_mode = ssl.CERT_NONE


def parse_json(data):
    info = json.loads(data)
    print('User count:', len(info))
    info = info['comments']

    lst = []
    for item in info:
        # print('Name: ', item['name'], "\t\t::\t", 'Count: ', item['count'])
        lst.append(item['count'])
    return lst


def get_data(url):
    data = urlopen(url, context=ctx).read()
    print('Retrieved', len(data), 'characters')
    print(data.decode())
    return data

def main():
    lst = parse_json(get_data(input('Enter - ').strip()))
    print(sum(lst))

main()
