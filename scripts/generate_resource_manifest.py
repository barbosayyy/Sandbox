import os
from datetime import datetime
import yaml
import argparse

parser = argparse.ArgumentParser(description='')
parser.add_argument("--target", type=int, default=0)
parser.add_argument("--cmake", type=int, default=0)

args = parser.parse_args()

if(args.cmake == 0):
    print("Resource Serializer Script Error: Not running as resource config")
    exit(-1)

if args.target < 0 or args.target > 1:
    print("Resource Serializer Script Error: No target mode")
    exit(-1)

# 0 - Debug
# 1 - Release
target_mode = args.target

resource_starting_id = 1

def get_value_from_ext_as_key(filename, dict):
    file_extension = os.path.splitext(filename)[-1].lower()
    return dict.get(file_extension, "")

type_count = {}

def create_yaml_data_from_folder(path, dict, data):
    for item in os.listdir(path):
        if os.path.isfile(os.path.join(path, item)):
            type_name = get_value_from_ext_as_key(item, dict)
            if type_name != "":
                if type_name not in data:
                    data[type_name] = []
                    type_count[type_name] = resource_starting_id
                data[type_name].append({
                    "id": type_count[type_name],
                    "name": item,
                    "path": os.path.join(path, item),
                })
                type_count[type_name] += 1
    return data

def sandbox_yaml_dump_resource_data(output_path, data):
    with open(output_path, "a") as file:
        yaml.dump(data, file)

def sandbox_yaml_dump_header_info(output_path):
    header = "#\n# Sandbox Engine Resource Manifest - generated at: " + datetime.now().strftime("%d/%m/%Y, %H:%M:%S") + "\n# Mode: " + str(target_mode) + "\n#\n\n"
    with open(output_path, "w") as file:
        file.write(header)

extension_dict = {
    ".png": "png",
    ".jpg": "jpg",
    ".vert": "vertex",
    ".frag": "fragment",
    ".obj": "obj",
    ".fbx": "fbx",
    ".txt": "text"
}

# Separate folder for resource-data.yaml?
if target_mode == 0:
    resource_path = os.getcwd().replace("\\build", "") + "\\resources"
elif target_mode == 1:
    resource_path = os.getcwd() + "\\resources"

resource_data_path = resource_path + "\\resource_manifest.yaml"
data = {}

for item in os.listdir(resource_path):
    folder_path = os.path.join(resource_path, item)
    if os.path.isdir(folder_path):
        if __debug__:
            print(item)
        create_yaml_data_from_folder(folder_path, extension_dict, data)

sandbox_yaml_dump_header_info(resource_data_path)
sandbox_yaml_dump_resource_data(resource_data_path, data)