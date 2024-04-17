import os

def generate_table_of_contents(directory):
    table_of_contents = "# Table of Contents\n\n"
    
    for filename in sorted(os.listdir(directory)):
        if filename.endswith(".md") and filename != "README.md":
            file_path = os.path.join(directory, filename)
            with open(file_path, 'r', encoding='utf-8') as file:
                title = file.readline().strip('#').strip()
                table_of_contents += f"- [{title}]({filename})\n"
    
    with open(os.path.join(directory, "README.md"), 'w', encoding='utf-8') as toc_file:
        toc_file.write(table_of_contents)

generate_table_of_contents(".")
