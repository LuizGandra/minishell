# Minishell

## Mandatório

### Tarefas
- [x] Exibir um prompt no terminal quando estiver aguardando por um novo comando
- [x] Criar o histórico de trabalho
- [x] Buscar e executar um programa (baseado na variável PATH usando um caminho absoluto ou relativo)
- [x] Tratar aspas simples `''`. Elas devem impedir o shell de interpretar meta-caracteres na sequência entre aspas.
- [x] Tratar aspas duplas `""`. Elas devem previnir o shell de interpretar meta-caracteres na sequência entre aspas, exceto o `$` (variáveis de ambiente).
- [x] Implementar os redirections:
	- [x] `<` redireciona o input.
	- [x] `>` redireciona o output.
	- [ ] `<<` recebe um delimitador e lê o input até a linha que contém o delimitador ser encontrada. *Ele não deve atualizar o histórico.*
	- [x] `>>` redireciona o output no append mode.
- [x] Implementar pipes (`|`). O output de cada comando na pipeline é conectado com o input do próximo comando via pipe.
- [ ]  Implementar variáveis de ambiente (`$`). Elas devem ser expandidas para o valor armazenado na variável.
- [x] Implementar o `$?`, que deve expandir para o exit status do último comando executado.
- [x] Implementar no modo interativo:
	- [x] `ctrl + C` deve exibir um novo prompt em uma nova linha.
	- [x] `ctrl + D` deve sair do shell.
	- [x] `ctrl + \` não deve fazer nada.
- [x] Implementar os seguintes builtins:
	- [x] `echo` com a flag `-n`.
	- [ ] `cd` com apenas um caminho relativo ou absoluto.
	- [x] `pwd` sem nenhuma flag.
	- [ ] `export` sem nenhuma flag.
	- [ ] `unset` sem nenhuma flag.
	- [ ] `env` sem nenhuma opção ou argumento.
	- [x] `exit` sem nenhuma opção.

### Proibições
- [ ] Não usar mais de uma variável global para indicar que recebeu um Unix Signal. *A variável global não pode prover nenhuma outra informação ou dado além do número do sinal recebido.*
- [x] Não interpretar aspas não fechadas ou caracteres especiais que não foram exigidos pelo subject, como `\` e `;`.

## Bônus
- [x] Implementar `&&` com parênteses para prioriedades.
- [x] Implementar `||` com parênteses para prioriedades.
- [ ] Implementar wildcards (`*`) para o diretório atual.
