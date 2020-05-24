# SSC5723 Sistemas Operacionais  - Modulo 3

Professor: Dr. Julio Cezar Estrella\
Alunos: Antonio Alessandro Rocha e Diego Frazatto Pedroso


***Simulador de Gerenciamento de Memória Virtual com Paginação***
-------------------

Na computação, memória virtual é uma técnica utiliza a memória secundária como cache para armazenamento secundário. As premissas para essa abordagem foram, em primeiro lugar, permitir o compartilhamento seguro e eficiente da memória entre vários programas e também remover os transtornos de programação de uma quantidade pequena e limitada na memória principal.

As funções básicas da memória virtual são:
* Paginação ou swapping, que possibilita a uma aplicação utilizar mais memória do que a fisicamente existente na memória da máquina;
* Realocação para assegurar que cada aplicação tenha o seu próprio espaço de endereçamento;
* Proteção para impedir que um processo utilize um endereço de memória que é destinado a outro componente, ou não lhe pertença.

Ferramentas e Tecnologias
-------------------
Todas os elementos apresentados pelo autores neste trabalho forem criados e testados utilizando uma máquina virtual Linux com a distribuição Ubuntu 16.04.6 LTS.

Exclusivamente para esse módulo, utilizamos a linguagem C++ para conter o excesso de estrutuda de dados que teriam de ser implementadas na linguagem C.

No arquivo **Properties.h** temos a classe *properties* para ler o arquivo de configuração da MMU e extrair os valores para o construtor na classe MMU.

No arquivo **Mmu.h** define e classe implementada dentro do arquivo **Mmu.cpp**, na qual a Unidade de Gerenciamento de Memória é desenvolvida. Esse componente traduz endereços virtuais em endereços físicos. A memória principal está separada entre a memória física e a memória lógica. Na primeira,a memória é implementada em circuitos digitais e é nela que a memória lógica é fisicamente armazenada, geralmente a memória lógica é maior do que a memória física. 

O simulador faz leitura do arquivo **simulation** linha a linha, coletando endereços de memória (binários) e são feitos os acessos de página, partindo do princípio que as páginas estão vazias, por esse motivo ocorre page fault nas primeiras páginas. Os tipos de acesso que interpretados pelo simulador são de escrita (W) e leitura (R).

Vale lembrar que, uma falta de página ou page fault, no contexto de gerenciamento de memória, é uma interrupçã disparada pelo hardware quando um programa acessa uma página mapeada no espaço de memória virtual, mas que não foi carregada na memória física do computador.

Toda vez que uma instrução é lida, exibe-se a página caso ela seja encontrada, caso contrário é disparado o page fault. Após cada nova instrução de acesso a memória, o simulador exibe o estados das páginas que estão na memória física, exibe o número da página, o valor booleano (TRUE | FALSE) do algoritmo segunda change, ou o tempo de acesso, implementado através do algoritmo LRU (Least Recently Used), que funciona como uma espécie de "idade" para cada página.

O algoritmo LRU [1] implementa um contador C de 64 bits incrementado a cada instrução (em hardware), cada entrada da tabela de páginas deve ter um campo extra para armazenar o valor do contador (campo C). A cada referência à memória o valor corrente de C é armazenado na entrada da tabela de páginas na posição correspondente à página referenciada. Quando ocorre um Page Fault, a tabela de páginas é examinada, a entrada cujo campo C é de menor valor é a escolhida.

No arquivo **config.cfc** os parâmetros ***“page_size”***, ***“logical_adress_size”***,***“physical_memory_size”*** e ***“replacement_algorithm”*** são fornecidos. Na paginação a memória física é dividida em blocos de bytes contíguos denominados molduras de páginas, geralmente com tamanho de 4 KiB. Por exemplo, se o usuário desejar o valor default dos blocos o parâmetro ***page_size***  deve ser igual a 4096 (2^12).

O simulador ainda exibe os eventos na memória principal na memória secundária, bem como a tabela de páginas associada e as ocorrências de falta de página.

Para compilar os códigos utilizamos o compilador ***g++***[2] através do comando:
````
$ g++ *.cpp -o main
````
Exemplo do simulador em execução:

````
$ ./main
````

````
 Page fault: 0!
Page 0: Counter: 0
Page -1: Counter: -1
 Page 0 found!
Page 0: Counter: 1
Page -1: Counter: -1
 Page fault: 3!
Page 0: Counter: 1
Page 3: Counter: 2
 Page fault: 1!
Page 1: Counter: 3

#include <iostream>
Page 3: Counter: 2
 Page fault: 2!
Page 1: Counter: 3
Page 2: Counter: 4
 Page 2 found!
Page 1: Counter: 3
Page 2: Counter: 5
 Page fault: 3!
Page 3: Counter: 6
Page 2: Counter: 5

# page_size in bits
 Page fault: 0!
Page 3: Counter: 6
Page 0: Counter: 7
 Page 0 found!
Page 3: Counter: 6
Page 0: Counter: 8
 Page 0 found!
Page 3: Counter: 6
Page 0: Counter: 9
 Page fault: 2!
Page 2: Counter: 10
Page 0: Counter: 9
P1 W 10001 Page 2 found!
Page 2: Counter: 11
Page 0: Counter: 9
````


![stats](/assets/stats.png)



Referências
-------------------
1. www.inf.ufes.br/~zegonc/material/Sistemas_Operacionais
2. www.geeksforgeeks.org/compiling-with-g-plus-plus/

Contatos 
-------------------
antonio.alessandro@usp.br\
diegopedroso@usp.br