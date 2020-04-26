# SSC5723 Sistemas Operacionais  - Modulo 2

Professor: Dr. Julio Cezar Estrella\
Alunos: Antonio Alessandro Rocha e Diego Frazatto Pedroso


***Produtor Consumidor***
-------------------

O problema do Produtor e o Consumidor consiste em um conjunto de processos que compartilham um mesmo buffer. Os processos chamados produtores colocam informação no buffer. Os processos chamados consumidores retiram informação deste buffer. 

Esse trabalho busca exemplificar de forma clara, situações de impasses que ocorrem no gerenciamento de processos de um Sistema Operacional

![stats](/assets/produtor-consumidor.jpg)

Para garantir o acesso a essas variáveis e garantir o sincronimos vamos utilizar semáforos. De forma análoga ao semáforo de trânsito, na computação é um componente que tem como função o controle de acesso a recursos compartilhados num ambiente multitarefa. Esta variável pode ser manipulada através de duas primitivas atómicas, isto é, que não podem ser interrompidas por processos.

As principais operações sobre semáforos são:

Inicialização
-------------------
Recebe como parâmetro um valor inteiro indicando a quantidade de processos que podem aceder a um determinado recurso.

Operação wait
-------------------
Decrementa o valor do semáforo. Se o semáforo está com valor zero, o processo é colocado em modo espera. Para receber um sinal, um processo executa o wait e bloqueia se o semáforo impedir a continuação da sua execução.

Operação signal
-------------------
Se o semáforo estiver com o valor zero e existir algum processo em espera, um processo será acordado. Caso contrário, o valor do semáforo é incrementado. Para enviar um sinal, um processo executa um signal.

A solução desse problema utilizou a biblioteca **pthreads** [3], a qual possibilita a programação de forma concorrente com as funções de: controle de threads, criação de threads, suspensão de threads, execução e controle de exclusão mútua por semáforos binários, para controle da seção crítica. 


***Compartilhamento de Buffer***
-------------------

Para controlarmos o acesso a essas variáveis e garantir o sincronismo nas operações, foram utilizados semáforos [1].

Na criação do buffer no arquivo (lista.h) 

A dimensão do buffer é denifida dinamicamente, o usuário define o tamanho na inicialização do programa.

A função ***getSemaphore*** [2] forcene acesso aos semárofos daquela região crítica, sendo eles o MUTEX para o semáforo binário, FULL e EMPTY para Produtor e Consumidor.


Para compilação do código:
````
gcc main.c lista.c -pthread -o main
````

Basicamente 3 parâmetros precisam ser fornecidos, são eles:
1. Tamanho do Buffer
2. Numero de threads Produtores
3. Número de threads Consumidores


O programa inicializa com o buffer vazio, se alguma thread consumidora tentar entrar na região crítica será bloqueada pelo semáforo, umas vez que não ha nada no buffer e nada pode ser consumido.
Apenas então quando o primeiro Produtor inserir algum dado no buffer, o semáforo associado, FULL, vai ser incrementado e threads consumidoras que estavam bloqueadas vão para o estado de pronto, podendo ou não ser escalonadas logo em seguida.

Os semáforos atuam apenas nas threads produtoras e consumidoras, a thread main não é afetada. 

Através da função pthread_join permite que a thread main aguarde o termino das outras threads (consumidor e produtor). Essa função também permite que a thread não seja escalonada para main, e finalize todos os processos e as threads associadas a esses processos.

Caso o buffer fosse inicializado de forma oposta, ou seja, cheio. Se a primeira thread fosse um produtor, iria tentar inserir algum dado, e seria bloqueado pelo semáforo pelo fato de o buffer estar cheio. Teria que aguardar então o escalonamento de um Consumidor que iria remover um elemento do buffer.


Referências
-------------------
1. https://lisha.ufsc.br/teaching/dos/ine5357-2004-1/work/g4/sincronismo/design.htm
2. http://www.yolinux.com/TUTORIALS/LinuxTutorialPosixThreads.html
3. https://pubs.opengroup.org/onlinepubs/7908799/xsh/pthread.h.html

Contatos 
-------------------
antonio.alessandro@usp.br\
diegopedroso@usp.br
