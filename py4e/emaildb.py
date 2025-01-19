import readline
import sqlite3

conn = sqlite3.connect('emaildb.sqlite')
cur = conn.cursor()
print("Opened database successfully")
print(cur)
cur.execute('DROP TABLE IF EXISTS Counts')

cur.execute('''
CREATE TABLE Counts (org TEXT, count INTEGER)''')

url = "http://www.py4e.com/code3/mbox.txt"

file = input("Enter filename: ").strip()
if len(file) < 1:
    file = "mbox.txt"

with open(file, 'r') as fh:
    count = 0
    for line in fh:
        if not line.startswith('From: '): continue
        pieces = line.split()
        email = pieces[1]
        domain = email.split('@')[1]
        cur.execute('SELECT count FROM Counts WHERE org = ? ', (domain,))
        row = cur.fetchone()
        print(row)
        if row is None:
            cur.execute('''INSERT INTO Counts (org, count)
                    VALUES (?, 1)''', (domain,))
        else:
            cur.execute('UPDATE Counts SET count = count + 1 WHERE org = ?',
                        (domain,))
        count = count + 1
        if count % 20 == 0:
            conn.commit()
    conn.commit()

# https://www.sqlite.org/lang_select.html
sqlstr = 'SELECT org, count FROM Counts ORDER BY count DESC LIMIT 10'

cur.execute("SELECT count FROM Counts WHERE org = ? ", ('asfdf',))
print(cur.fetchone())

for row in cur.execute(sqlstr):
    print(str(row[0]), row[1])

cur.close()
