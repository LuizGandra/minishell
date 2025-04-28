#!/bin/zsh

# COLORS
RED='\033[0;31m'
GREEN='\033[0;32m'
CYAN='\033[0;36m'
YELLOW='\033[0;33m'
NC='\033[0m'

if [[ $# -eq 0 ]]; then
	echo "${RED}Uso: $0 <parent|child|dual>${NC}"
	exit 1
fi
if [[ $1 == "child" ]]; then
	config='[
				{
					"description": "Seguir o processo filho",
					"text": "set follow-fork-mode child",
					"ignoreFailures": true
				}
			]'
elif [[ $1 == "dual" ]]; then
	config='[
				{
					"description": "Não desanexar do processo filho",
					"text": "set detach-on-fork off",
					"ignoreFailures": true
				},
				{
					"description": "Seguir o pai por padrão",
					"text": "set follow-fork-mode parent",
					"ignoreFailures": true	
				}
			]'
elif [[ $1 == "parent" ]]; then
	config='[
				{
					"description": "Seguir o processo pai",
					"text": "set follow-fork-mode parent",
					"ignoreFailures": true
				}
			]'
else
	echo "${RED}Uso: $0 <parent|child|dual>${NC}"
	exit 1
fi

mkdir -p .vscode

cat > .vscode/tasks.json <<EOF
{
    "version": "2.0.0",
    "tasks": [
        {
            "label": "build",
            "type": "shell",
            "command": "make",
            "group": {
                "kind": "build",
                "isDefault": true
            }
        }
    ]
}
EOF

cat > .vscode/launch.json <<EOF
{
    "version": "0.2.0",
    "configurations": [
        {
            "name": "Debug (make)",
            "type": "cppdbg",
            "request": "launch",
            "program": "\${workspaceFolder}/minishell",
            "args": [],
            "stopAtEntry": false,
            "cwd": "\${workspaceFolder}",
            "environment": [],
            "externalConsole": false,
            "MIMode": "gdb",
            "setupCommands": $config,
            "miDebuggerPath": "/usr/bin/gdb",
            "preLaunchTask": "build",
            "miDebuggerArgs": "",
            "logging": {
                "moduleLoad": false,
                "trace": false,
                "engineLogging": false
            }
        }
    ]
}
EOF

echo "${CYAN}Arquivos .vscode/tasks.json e .vscode/launch.json criados!\n${NC}"
if [[ $1 == "dual" ]]; then
	echo "${GREEN}Para manipular os processos é preciso escrever no debugger do vscode os comandos abaixo:${NC}"
	echo "	${YELLOW}-exec${CYAN} info inferiors${NC}: Mostra todos os processos em andamento"
	echo "	${YELLOW}-exec${CYAN} inferior <n>${NC}: Muda o processo atual para o processo de número <n>"
fi
