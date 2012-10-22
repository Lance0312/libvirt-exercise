from xml.etree import ElementTree
import sys,re

tree = ElementTree.parse('../templates/domain.xml')
root = tree.getroot()

if len(sys.argv) == 3:
  domain_name = root.find('./name')
  domain_vol = root.find('./devices/disk/source')
  domain_name_text = domain_name.text
  domain_vol_text = domain_vol.get('file')
  for i in range(int(sys.argv[1]), int(sys.argv[1]) + int(sys.argv[2])):
    domain_name.text = domain_name_text + str(i)
    domain_vol.set('file', re.sub(domain_name_text, domain_name.text, domain_vol_text))
    tree.write('../xml/domain%s.xml' % i)
else:
  print 'Output default xml description'
  tree.write('../xml/domain.xml')


