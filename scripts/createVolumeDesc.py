from xml.etree import ElementTree
import sys,re

tree = ElementTree.parse('../templates/volume.xml')
root = tree.getroot()

if len(sys.argv) == 3:
  volume_name = root.find('./name')
  volume_path = root.find('./target/path')
  volume_name_text = volume_name.text
  volume_path_text = volume_path.text
  for i in range(int(sys.argv[1]), int(sys.argv[1]) + int(sys.argv[2])):
    volume_name.text = volume_name_text + str(i)
    volume_path.text = re.sub(volume_name_text, volume_name.text, volume_path_text)
    tree.write('../xml/volume%s.xml' % i)
else:
  print 'Output default xml description'
  tree.write('../xml/volume.xml')

