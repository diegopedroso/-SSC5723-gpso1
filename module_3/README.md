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

No arquivo **Properties.h** temos a classe *Properties* para ler o arquivo de configuração da MMU e extrair os valores para o construtor da classe MMU.

No arquivo **Mmu.h** define e classe implementada dentro do arquivo **Mmu.cpp**, na qual a Unidade de Gerenciamento de Memória é desenvolvida. Esse componente traduz endereços virtuais em endereços físicos. A memória principal está separada entre a memória física e a memória lógica. Na primeira,a memória é implementada em circuitos digitais e é nela que a memória lógica é fisicamente armazenada, geralmente a memória lógica é maior do que a memória física. 

O simulador faz leitura do arquivo **simulation** linha a linha, coletando endereços de memória (binários) e são feitos os acessos de página, partindo do princípio que as páginas estão vazias, por esse motivo ocorre page fault nas primeiras páginas. Os tipos de acesso que interpretados pelo simulador são de escrita (W) e leitura (R).

O simulador faz leitura do arquivo **simulation.txt** linha a linha, coletando endereços de memória (binários) e são feitos os acessos de página, partindo do princípio que as páginas estão ausentes, por esse motivo ocorre falta de página nas primeiros acessos às páginas. Os tipos de acesso interpretados pelo simulador são de escrita em um endereço (W), leitura em um endereço (R), execução de uma instrução em um endereço (I) e acesso a um dispositivo de E/S.

Vale lembrar que uma falta de página, no contexto de gerenciamento de memória, é uma interrupção disparada pelo hardware quando um programa acessa uma página mapeada no espaço de memória virtual, mas que não foi carregada na memória física do computador.

Toda vez que uma instrução é lida, exibe-se a página caso ela seja encontrada, caso contrário é disparado o page fault. Nesse caso, caso a memória física esteja cheia, a página que foi escolhida pelo algoritmo de substituição de páginas para sair da RAM é exibida e a nova é carregada do disco para a memória.

O algoritmo LRU [1] implementa um contador C de 64 bits incrementado a cada instrução (em hardware), cada entrada da tabela de páginas deve ter um campo extra para armazenar o valor do contador (campo C). A cada referência à memória o valor corrente de C é armazenado na entrada da tabela de páginas na posição correspondente à página referenciada. Quando ocorre uma falta de página, a tabela de páginas é examinada e a entrada cujo campo C é de menor valor é a escolhida a ser substituída.

No arquivo **config.cfg** os parâmetros ***“page_size”***, ***“logical_adress_size”***,***“physical_memory_size”***, ***“replacement_algorithm”*** e ***“swap_size”*** são fornecidos. Na paginação a memória física é dividida em blocos de bytes contíguos denominados molduras de páginas, geralmente com tamanho de 4 KiB. Por exemplo, se o usuário desejar o valor default dos blocos o parâmetro ***page_size***  deve ser igual a 4096 (2^12).

Além de instruções de acesso a memória e dispositivos, há também a de criação de processos. Nesse caso, o simulador checará se há espaço disponível para a sua devida alocação, ou seja, se há espaço na RAM ou se algum processo pode ser movido para a área de swap. Caso contrário, o processo não é criado e a simulação é abortada.

Para compilar os códigos utilizamos o compilador ***g++***[2] através do comando:
````
$ g++ *.cpp -o main
````
Exemplo do simulador em execução:

````
$ ./main
````
Saída para a configuração e simulação dada no repositório.
````
------------------------------------------------------------
Replacement algorithm: LRU
Page size (in bits): 4096
Physical memory size (in pages): 4
Swap area size (in pages): 8
Logical address size (in bits): 16
------------------------------------------------------------
P1 C 2

Process 1 created successfully
------------------------------------------------------------
P1 R 0010000000000000

Process 1 accessing memory at 0010000000000000
Page fault 2!
------------------------------------------------------------
P1 R 0101001000000000

Process 1 accessing memory at 0101001000000000
Page fault 5!
------------------------------------------------------------
P1 P 0010000100010000

Process 1 running instruction at 0010000100010000
Page 2 found!
------------------------------------------------------------
P1 R 0001000000000010

Process 1 accessing memory at 0001000000000010
Page fault 1!
------------------------------------------------------------
P1 P 0101000000000010

Process 1 running instruction at 0101000000000010
Page 5 found!
------------------------------------------------------------
P1 W 0010001000000000

Process 1 accessing memory at 0010001000000000
Page 2 found!
------------------------------------------------------------
P7 C 3

Process 7 created successfully
------------------------------------------------------------
P7 R 0100011111111111

Process 7 accessing memory at 0100011111111111
Page fault 4!
------------------------------------------------------------
P7 R 0101001100100000

Process 7 accessing memory at 0101001100100000
Page 5 found!
------------------------------------------------------------
P7 I 1111000000000010

Process 7 accessing device 61442
------------------------------------------------------------
P7 R 0011001100100001

Process 7 accessing memory at 0011001100100001
Page fault 3!
Page 1 removed from RAM
------------------------------------------------------------
P7 W 0010100000000000

Process 7 accessing memory at 0010100000000000
Page 2 found!
------------------------------------------------------------
P1 R 0101000000000011

Process 1 accessing memory at 0101000000000011
Page 5 found!
------------------------------------------------------------
P1 R 0010000000000100

Process 1 accessing memory at 0010000000000100
Page 2 found!
------------------------------------------------------------
P1 W 1111010000000001

Process 1 accessing memory at 1111010000000001
Page fault 15!
Page 4 removed from RAM
------------------------------------------------------------
P1 W 1001010000000010

Process 1 accessing memory at 1001010000000010
Page fault 9!
Page 3 removed from RAM
------------------------------------------------------------
P1 P 0101111111111111

Process 1 running instruction at 0101111111111111
Page 5 found!
------------------------------------------------------------
P2 C 4

Process 2 created successfully
------------------------------------------------------------
P3 C 4

Memory is full! Process could not be created!
Aborting...
````

Referências
-------------------
1. www.inf.ufes.br/~zegonc/material/Sistemas_Operacionais
2. www.geeksforgeeks.org/compiling-with-g-plus-plus/

Contatos 
-------------------
antonio.alessandro@usp.br\
diegopedroso@usp.br
