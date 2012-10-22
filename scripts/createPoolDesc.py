from xml.etree import ElementTree
import sys,re

tree = ElementTree.parse('../templates/pool.xml')
root = tree.getroot()

if len(sys.argv) == 2:
  pool_name = root.find('./name')
  pool_path = root.find('./target/path')
  pool_name_text = pool_name.text
  pool_path_text = pool_path.text
  pool_name.text = sys.argv[1]
  pool_path.text = re.sub(pool_name_text, sys.argv[1], pool_path_text)
else:
  print 'Output default xml description'

tree.write('../xml/pool.xml')
