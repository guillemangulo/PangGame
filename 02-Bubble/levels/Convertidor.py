import xml.etree.ElementTree as ET
import glob
import os

# Agafo tots els nivells del directory
tmx_files = glob.glob('*.tmx')

for tmx_file in tmx_files:
    print("Convertint "+tmx_file)
    # Parsejo els archius del Tiled
    tree = ET.parse(tmx_file)
    mapa = tree.getroot()

    # Parsejo l'arxiu asociat de tileset
    tsx_file = tree.find("tileset").attrib['source']
    tree = ET.parse(tsx_file)
    tilesetFile = tree.getroot()
    
    # Extrec les dades avans de formatejarles
    width = int(mapa.attrib['width'])
    height = int(mapa.attrib['height'])
    blockSize = int(mapa.attrib['tilewidth'])
    imageSource = '/'.join(tsx_file.split('/')[1:-1]) +"/"+tilesetFile.find('image').attrib['source']
    columns = int(tilesetFile.attrib['columns'])
    rows = int(int(tilesetFile.attrib['tilecount'])/columns)
    tileSize = int(tilesetFile.attrib['tilewidth'])

    # Creo el nou archiu amb el mateix nom pero en txt
    output_file = os.path.splitext(tmx_file)[0] + ".txt"

    # Enganxo tota l'informaciò obtenida
    with open(output_file, 'w') as f:
        f.write("TILEMAP\n")
        f.write(f"{width} {height} \n")
        f.write(f"{tileSize} {blockSize} \n")
        f.write(f"{imageSource} \n")
        f.write(f"{columns} {rows} \n")
        
        # Ara vaig capa a capa possant el nom i el csv
        for layer in mapa.findall('layer'):
            name = layer.attrib['name']
            f.write(f"CAPA {name}\n")
            data = layer.find('data').text.strip()
            f.write(data + "\n")

print("Conversió completada!")