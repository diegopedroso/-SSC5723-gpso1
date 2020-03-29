# SSC5723 Sistemas Operacionais  - Modulo 1 

Professor: Dr. Julio Cezar Estrella\
Alunos: Antonio Alessandro Rocha e Diego Frazatto Pedroso


***Chamadas de Sistema***
-------------------

Na computação, uma chamada de sistema ou **system call** é o mecanismo programático pelo qual um programa de computador solicita um serviço ao Kernel sobre o qual ele está sendo executado. Isto inclui serviços relacionados ao hardware, como acessar um periférico), criação e execução de novos processos e comunicação com serviços do núcleo de maneira integral como escalonamento do processador. 


Ferramentas e Tecnologias
-------------------
Todas os elementos apresentados pelo autores neste trabalho forem criados e testados utilizando uma máquina virtual Linux com a distribuição Ubuntu 16.04.6 LTS.

1. ***GCC***

A GCC [2] inclui front-ends para C além de diversas bibliotecas, foi originalmente escrito como o compilador para o sistema operacional GNU. Todos os códigos utilizandos para operar as chamadas de sistemas foram compilados utilizando o compilador GCC, utilizando o seguinte comando para geração dos executáveis.

````
gcc code.c -o bin_name
````

2. ***Strace***

O Strace [1] é uma ferramenta que monitora as chamadas de sistema e os sinais recebidos pela aplicação. A maneira mais comum de executá-la é passando a aplicação a ser monitorada como parâmetro, como no exemplo abaixo.

````
strace -o analytics/processo/open_sc -e open bin/processo
````

Por padrão, o Strace exibe todas as chamadas do sistema para o binário especificado. Para exibir apenas uma chamada de sistema específica, utilizou-se o parâmetro -e. Para ambos os exemplos também se fez uso do parâmetro -o, que redireciona a saída do comando para um arquivo

Usando o parâmetro -c, o Strace fornece um relatório estatístico útil para o rastreamento de execução

````
strace -o analytics/processo/stats.txt -c open bin/processo
````

A coluna "calls" na saída a seguir indica quantas vezes essa chamada específica do sistema foi executada.


![stats](/assets/stats.png)


No trecho do código processo.c, temos a chama de sistema ***fork()***.

![stats](/assets/process-c.png)


Na análise do binário utilizando o Strace, a chamada de sistema fork() não aparece como uma chamada dentro do log do Strace. 

Ocorre que, a chamada fork() quando escrita na linguagem C, utiliza a biblioteca glibc, que por sua vez implementa o fork() como um wrapper da chamada de sistema Clone, que podem ser observadas abaixo.

![stats](/assets/process-ana.png)

Na coluna "syscall" é possível observar a chamada de sistema clone, que implementa o fork() em baixo nível.


***Processos CPU-bound e I-O bound***
-------------------

Na computação, I-O bound é um termo utilizado para designar os sistemas que fazem uso intensivo de entrada e saída. Todos os sistemas operacionais executam processos de entrada e saída. Por exemplo, quando algum usuário quer copiar um arquivo para algum periférico (pen drive). Esses processos são conhecidos como I/O bound porque fazem pouco uso da CPU. Por outro lado, existem processos conhecidos como CPU bound, que fazem muito uso da CPU, a citar alguns jogos eletrônicos que utilizam recursos gráficos em 3D de alta complexidade.


Utilizamos um comando nativo do Linux para aferir os tempos de execução de cada binário.

```
time /bin/io_bound
```

O Linux é projetado de tal forma que ele examina o cache de disco antes de examinar o disco, portanto se encontrar o recurso solicitado no cache, a solicitação não atingirá o disco; E no caso de limparmos o cache, o sistema operacional procurará o recurso no disco novamente, não causando perdas ou problemas para o próprio sistema ou o usuário. Os comandos abaixo fazem uma limpeza da memória cache sem que você precise reiniciar o sistema operacional.

```
echo 3 > /proc/sys/vm/drop_caches
````

```
sysctl -w vm.drop_caches=3
```

Foram executadas várias rodadas de testes, os resultados de tempo de execução eram inseridos juntamente aos comandos de limpeza de cache, para que a alta repetição dos comandos não intereferisse no resultado do experimento. No total foram executados 166 rodadas para cada binário, abaixo vemos o resultado do cpu_bound. As medidas estatísticas análisadas foram: média aritmética, percentil 99 (com o objetivo de eliminar outliers) e o desvio padrão dos elementos da amostra.

|      | media    | p99      | desvpad  |
|------|----------|----------|----------|
| real | 0m0.003s | 0m0.005s | 0m0.001s |
| user | 0m0.005s | 0m0.005s | 0m0.001s |
| sys  | 0m0.001s | 0m0.000s | 0m0.001s |

Os valores do binário io_bound seguiram os mesmo critérios de avaliação, e podem ser observador na tabela abaixo.

|      | media    | p99      | desvpad  |
|------|----------|----------|----------|
| real | 0m0.248s | 0m0.230s | 0m0.127s |
| user | 0m0.186s | 0m0.170s | 0m0.007s |
| sys  | 0m0.023s | 0m0.019s | 0m0.008s |


Paralelamente, fizemos outra análise utilizando o mesmo comando, porém a chamada é de outra forma.
Quando executa o comando time, um comando shell incorporado [e executado, e esse comando não suporta todos os recursos.

O comando /usr/bin/time é executado em tempo real do GNU Linux.

Alguns parametros adicionais foram passando na execução do comando para facilitar a extração e análise das informações.

```
/usr/bin/time --format="Uso de %P da CPU\n%Ss em modo kernel\n%Us em modo usurio\n%c Trocas de contexto involuntarias\n%w Trocas de contexto vontunarias" ./bin
```

Para o binário cpu_bound temos:

Uso de 90% da CPU
0.00s em modo kernel
0.00s em modo usurio
5 Trocas de contexto involuntárias
1 Trocas de contexto voluntárias

Para o binário io_bound temos:

Uso de 99% da CPU
0.01s em modo kernel
0.19s em modo usurio
20 Trocas de contexto involuntárias
1 Trocas de contexto voluntárias


Referências
-------------------
[1] http://man7.org/linux/man-pages/man1/strace.1.html\
[2] https://gcc.gnu.org/

Contatos 
-------------------
antonio.alessandro@usp.br\
diegopedroso@usp.br