from urllib.request import urlopen
from bs4 import BeautifulSoup
import ssl

# Ignore SSL certificate errors
ctx = ssl.create_default_context()
ctx.check_hostname = False
ctx.verify_mode = ssl.CERT_NONE

def get_link(url, pos):
    html = urlopen(url, context=ctx).read()
    soup = BeautifulSoup(html, "html.parser")
    tags = soup('a')
    links = []
    for tag in tags:
        links.append(tag.get('href', None))
        # Look at the parts of a tag
        # print('URL:', tag.get('href', None))
        # print('TAG:', tag)
        # print('Contents:', tag.contents[0])
        # print('Attrs:', tag.attrs)
    return links[pos]
#
#  def main():
#      url = input('Enter base URL - ').strip()
#      count = int(input('Enter count: ').strip())
#      pos = int(input('Enter position: ').strip())
#      link = url
#      for i in range(count):
#          link = get_link(link, pos - 1)
#          print(link)
#
#  main()
