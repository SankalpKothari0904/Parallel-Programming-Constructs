import os

def generate_table_of_contents(directory):
    table_of_contents = "# Table of Contents\n\n"
    
    # Get list of files in the directory with their creation times
    files_with_creation_times = []
    for filename in os.listdir(directory):
        if filename.endswith(".md") and filename != "README.md":
            file_path = os.path.join(directory, filename)
            creation_time = os.path.getctime(file_path)
            files_with_creation_times.append((filename, creation_time))
    
    # Sort files based on creation time
    sorted_files = sorted(files_with_creation_times, key=lambda x: x[1])
    
    # Generate table of contents
    for filename, _ in sorted_files:
        file_path = os.path.join(directory, filename)
        with open(file_path, 'r', encoding='utf-8') as file:
            title = file.readline().strip('#').strip()
            table_of_contents += f"- [{title}]({filename})\n"
    
    # Write table of contents to README.md
    with open(os.path.join(directory, "README.md"), 'w', encoding='utf-8') as toc_file:
        toc_file.write(table_of_contents)

generate_table_of_contents(".")
