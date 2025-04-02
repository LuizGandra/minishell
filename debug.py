import os
import json

# Diretório de configuração do VSCode
vscode_dir = ".vscode"
os.makedirs(vscode_dir, exist_ok=True)

# Conteúdo do tasks.json
tasks = {
    "version": "2.0.0",
    "tasks": [
        {
            "label": "build",
            "type": "shell",
            "command": "make",
            "group": {
                "kind": "build",
                "isDefault": True
            }
        }
    ]
}

# Conteúdo do launch.json
launch = {
    "version": "0.2.0",
    "configurations": [
        {
            "name": "Debug (make)",
            "type": "cppdbg",
            "request": "launch",
            "program": "${workspaceFolder}/minishell",
            "args": [],
            "stopAtEntry": False,
            "cwd": "${workspaceFolder}",
            "environment": [],
            "externalConsole": True,
            "MIMode": "gdb",
            "setupCommands": [
                {
                    "description": "Habilitar exibição das variáveis",
                    "text": "-enable-pretty-printing",
                    "ignoreFailures": True
                }
            ],
            "miDebuggerPath": "/usr/bin/gdb",
            "preLaunchTask": "build",
            "miDebuggerArgs": "",
            "logging": {
                "moduleLoad": False,
                "trace": False,
                "engineLogging": False
            }
        }
    ]
}

# Função para salvar JSON
def save_json(filename, content):
    with open(os.path.join(vscode_dir, filename), "w") as f:
        json.dump(content, f, indent=4)

# Criando os arquivos
save_json("tasks.json", tasks)
save_json("launch.json", launch)

print("Arquivos .vscode/tasks.json e .vscode/launch.json foram criados com sucesso!")
