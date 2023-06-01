import polygenerator as pl


ms = str()
for i in range(100):
    ms += f'Polygon* createExample{i}()' + '{\n'
    ms += "    Point pointsList[] = {"

    n = 0
    if i<5: n=4
    elif i<20: n=8
    elif i<50: n=14
    else: n =20

    p = pl.random_polygon(n)
    t = [(round(500*i[0]), round(500*i[1])) for i in p]
    for o in t :
        x, y = o
        ms += '{'+str(o[0])+', '+str(o[1])+'}' +','
    ms = ms[:-1]+'};\n'+f'    return createPolygon(pointList, {n});\n' + '}\n\n'

with open('examples.c', 'w') as f:
    f.write(ms)
