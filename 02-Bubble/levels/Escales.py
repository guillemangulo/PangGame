import os
import xml.etree.ElementTree as ET
import re

# Get the list of TMX files in the same folder as the script
folder_path = os.path.dirname(os.path.abspath(__file__))
tmx_files = [file for file in os.listdir(folder_path) if file.endswith('.tmx')]

# Iterate through each TMX file
for tmx_file in tmx_files:
    # Parse the TMX file
    tree = ET.parse(tmx_file)
    root = tree.getroot()
    print(f'Processing {tmx_file}...')

    latest_layer = root.findall('layer')[-1]
    latest_layer_id = int(latest_layer.get('id'))
    new_layer_id = latest_layer_id + 1
    new_layer_name = 'Stairs'
    new_layer_width = latest_layer.get('width')
    new_layer_height = latest_layer.get('height')

    # Create a new layer for interactive
    interactive_layer = ET.SubElement(root, 'layer')
    interactive_layer.set('id', '2')
    interactive_layer.set('name', 'Interactiva')
    interactive_layer.set('width', new_layer_width)
    interactive_layer.set('height', new_layer_height)

    # Create a 2D array for the interactive_layer_data
    interactive_layer_data = ET.SubElement(interactive_layer, 'data', encoding='csv')
    interactive_layer_data.text = ''

    interactive_layer_2d = [['0' for _ in range(int(new_layer_width))] for _ in range(int(new_layer_height))]

    for layer in root.findall('layer'):
        if layer.get('name') == 'Interactive':
            # Iterate through each tile in the layer
            for data in layer.findall('data'):
                tile_ids = data.text.split(',')
                # Update the interactive_layer_2d

                for i, tile_id in enumerate(tile_ids):
                    tile_id = tile_id.strip()  # Strip newline character from tile_id
                    row = i // int(new_layer_width)
                    col = i % int(new_layer_width)
                    if tile_id and (interactive_layer_2d[row][col] == '0' or interactive_layer_2d[row][col] == '\n0'):
                        interactive_layer_2d[row][col] = tile_id

    # Iterate through each layer
    for layer in root.findall('layer'):
        if layer.get('name') == 'Background':
            # Iterate through each tile in the layer
            for data in layer.findall('data'):
                tile_ids = data.text.split(',')
                # Update the interactive_layer_2d

                for i, tile_id in enumerate(tile_ids):
                    tile_id = tile_id.strip()  # Strip newline character from tile_id
                    row = i // int(new_layer_width)
                    col = i % int(new_layer_width)
                    if tile_id and (interactive_layer_2d[row][col] == '0' or interactive_layer_2d[row][col] == '\n0'):
                        interactive_layer_2d[row][col] = tile_id


    # Update the interactive_layer_data text
    interactive_layer_data.text = '\n'+ ',\n'.join([','.join(row) for row in interactive_layer_2d])

    # Remove the old Background and Interactive layers
    root.findall('layer')
    for layer in root.findall('layer'):
        if layer.get('name') == 'Background' or layer.get('name') == 'Interactive':
            root.remove(layer)

    
    # Create a new layer for stairs
    new_layer = ET.SubElement(root, 'layer')
    new_layer.set('id', '1')
    new_layer.set('name', new_layer_name)
    new_layer.set('width', new_layer_width)
    new_layer.set('height', new_layer_height)

    # Create the stairs_layer_data outside the layer loop
    stairs_layer_data = ET.SubElement(new_layer, 'data', encoding='csv')
    stairs_layer_data.text = ''

    # Create a 2D array for the stairs_layer_data
    stairs_layer_2d = [['0' for _ in range(int(new_layer_width))] for _ in range(int(new_layer_height))]

    # Iterate through each layer
    for layer in root.findall('layer'):
        # Iterate through each tile in the layer
        for data in layer.findall('data'):
            # Replace specific tiles with numbers 16, 17, and 18
            tile_ids = data.text.split(',')
            updated_tile_ids = [tile_id if tile_id not in ['16', '17', '18'] else '0' for tile_id in tile_ids]
            data.text = ','.join(updated_tile_ids)

            # Update the stairs_layer_2d
            for i, tile_id in enumerate(tile_ids):
                row = i // int(new_layer_width)
                col = i % int(new_layer_width)
                if tile_id in ['16', '17', '18'] and stairs_layer_2d[row][col] == '0':
                    stairs_layer_2d[row][col] = tile_id

    # Update the stairs_layer_data text
    stairs_layer_data.text ='\n'+ ',\n'.join([','.join(row) for row in stairs_layer_2d])

    # Save the modified TMX file
    tree.write(tmx_file)

    # Save the modified TMX file
    xmlstr = ET.tostring(root, encoding='unicode')
    xmlstr = re.sub('>(?!\n)', '>\n', xmlstr)
    with open(tmx_file, "w") as f:
        f.write(xmlstr)


    print('Background layer and old interactive layer removed, and merged into the new interactive layer successfully.')

print('Done!')