# SSC5723 Sistemas Operacionais  - Modulo 1 

Professor: Dr. Julio Cezar Estrella\
Alunos: Antonio Alessandro Rocha e Diego Frazatto Pedroso


Chamadas ao Sistema 
-------------------

Na computação, uma chamada de sistema (system call) é o mecanismo programático pelo qual um programa de computador solicita um serviço ai kernel sobre o qual ele está sendo executado. Isto pode incluir serviços relacionados ao hardware (por exemplo, acessar uma unidade de disco rígido), criação e execução de novos processos e comunicação com serviços do núcleo de maneira integral como escalonamento do processador. 


Ferramentas e Tecnologias
-------------------

Strace

````
strace -o analytics/processo/open_sc -e open bin/processo
````

````
strace -o analytics/processo/stats.txt -c open bin/processo
````

![stats](/assets/stats.png)



Processos CPU-bound e I-O bound 

```
time /bin/io_bound
```

Referências
-------------------
[1] http://man7.org/linux/man-pages/man1/strace.1.html
[2] 

Contatos 
-------------------
antonio.alessandro@usp.br
diegopedroso@usp.br