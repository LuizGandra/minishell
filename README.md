# Minishell

## Mandatório

### Tarefas
- [ ] Exibir um prompt no terminal quando estiver aguardando por um novo comando
- [ ] Criar o histórico de trabalho (lista de comandos?)
- [ ] Buscar e executar um programa (baseado na variável PATH usando um caminho absoluto ou relativo)
- [ ] Tratar aspas simples `''`. Elas devem impedir o shell de interpretar meta-caracteres na sequência entre aspas.
- [ ] Tratar aspas duplas `""`. Elas devem previnir o shell de interpretar meta-caracteres na sequência entre aspas, exceto o `$` (variáveis de ambiente).
- [ ] Implementar os redirections:
	- [ ] `<` redireciona o input.
	- [ ] `>` redireciona o output.
	- [ ] `<<` recebe um delimitador e lê o input até a linha que contém o delimitador ser encontrada. *Ele não deve atualizar o histórico.*
	- [ ] `>>` redireciona o output no append mode.
- [ ] Implementar pipes (`|`). O output de cada comando na pipeline é conectado com o input do próximo comando via pipe.
- [ ] Implementar variáveis de ambiente (`$`). Elas devem ser expandidas para o valor armazenado na variável.
- [ ] Implementar o `$?`, que deve expandir para o exit status do último comando executado.
- [ ] Implementar no modo interativo:
	- [ ] `ctrl + C` deve exibir um novo prompt em uma nova linha.
	- [ ] `ctrl + D` deve sair do shell.
	- [ ] `ctrl + \` não deve fazer nada.
- [ ] Implementar os seguintes builtins:
	- [ ] `echo` com a flag `-n`.
	- [ ] `cd` com apenas um caminho relativo ou absoluto.
	- [ ] `pwd` sem nenhuma flag.
	- [ ] `export` sem nenhuma flag.
	- [ ] `unset` sem nenhuma flag.
	- [ ] `env` sem nenhuma opção ou argumento.
	- [ ] `exit` sem nenhuma opção.

### Proibições
- [ ] Não usar mais de uma variável global para indicar que recebeu um Unix Signal. *A variável global não pode prover nenhuma outra informação ou dado além do número do sinal recebido.*
- [ ] Não interpretar aspas não fechadas ou caracteres especiais que não foram exigidos pelo subject, como `\` e `;`.

## Bônus
- [ ] Implementar `&&` com parênteses para prioriedades.
- [ ] Implementar `||` com parênteses para prioriedades.
- [ ] Implementar wildcards (`*`) para o diretório atual.