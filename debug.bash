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
            "externalConsole": true,
            "MIMode": "gdb",
            "setupCommands": [
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
			],
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

echo "Arquivos .vscode/tasks.json e .vscode/launch.json criados!"
