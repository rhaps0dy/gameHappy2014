from lxml import etree
from sys import exit, argv
import numpy

nom=''
if(len(argv)>2):
	print('Usage: python feslevel.py <svg file>')
	exit()
if(len(argv)==2):
    nom=argv[1]
else:
    nom='drawing.svg'

list = []
a = etree.parse(nom)
for elem in a.iter():
	if elem.tag=='{http://www.w3.org/2000/svg}rect':
		x = float(elem.get('x'))
		y = float(elem.get('y'))
		w = float(elem.get('width'))
		h = float(elem.get('height'))
		transform = elem.get('transform')
		if transform!=None:
			if transform.startswith('translate'):
				amount = transform[10:-1].split(',')
				x += float(amount[0])
				y += float(amount[1])
			if transform.startswith('scale'):
				amount = transform[6:-1].split(',')
				w *= float(amount[0])
				h *= float(amount[1])
				if(w < 0):
					x += w
					w *= -1
				if(h < 0):
					y += h
					h *= -1
			if transform.startswith('matrix'):
				amount = transform[7:-1].split(',')
				transf = numpy.matrix([[float(amount[0]), float(amount[2]), float(amount[4])],
									[float(amount[1]), float(amount[3]), float(amount[5])],
									[0, 0, 1]])
				pos1 = numpy.matrix([[x], [y], [1]])
				pos2 = numpy.matrix([[x+w], [y+h], [1]])
				newpos1 = transf*pos1
				newpos2 = transf*pos2
				w = newpos2[0,0]-newpos1[0,0]
				h = newpos2[1,0]-newpos1[1,0]
				x = newpos1[0,0]
				y = newpos1[1,0]
				if(w < 0):
					x += w
					w *= -1
				if(h < 0):
					y += h
					h *= -1
		list.append((x, y, w, h))
		print(x, y, w, h)

out = open('level', 'w')
out.write(str(len(list))+'\n')
for tuple in list:
	for num in tuple:
		out.write(str(num)+' ')
	out.write('\n')
out.close()
