# SSC5723 Sistemas Operacionais  - Modulo 4

Professor: Dr. Julio Cezar Estrella\
Alunos: Antonio Alessandro Rocha e Diego Frazatto Pedroso


***Sistemas de Arquivos***
-------------------

Na computação, um sistema de arquivos é um conjunto de estruturas lógicas e de rotinas, que permitem ao sistema operacional controlar o acesso ao disco rígido. Diferentes sistemas operacionais usam diferentes sistemas de arquivos. Conforme cresce a capacidade dos discos e aumenta o volume de arquivos e acessos, esta tarefa torna-se mais e mais complicada, exigindo o uso de sistemas de arquivos cada vez mais complexos e robustos.


Ferramentas e Tecnologias
-------------------
Todas os elementos apresentados pelo autores neste trabalho forem criados e testados utilizando uma máquina virtual Linux com a distribuição Ubuntu 16.04.6 LTS.

1 - ***NTFS***\

O NTFS [1] foi desenvolvido quando a Microsoft decidiu criar o Windows NT: como o WinNT deveria ser um sistema operacional mais completo e confiável, o FAT não servia como sistema de arquivos por causa de suas limitações e falta de recursos Anteriormente, ela já havia tentado fazer isso em parceria com a IBM, lançando o OS/2 - no entanto as duas empresas divergiam em certos pontos e acabaram quebrando a aliança. 

O OS/2 usava o sistema de arquivos HPFS (High Performance File System - Sistema de Arquivos de Alta Performance), cujos conceitos acabaram servindo de base. O NTFS possui uma estrutura que armazena as localizações de todos os arquivos e diretórios, incluindo os arquivos referentes ao próprio sistema de arquivos denominado MFT (Master File Table).

2 - ***FAT32***\

O FAT32 [2] (File Allocation Table ou Tabela de Alocação de Arquivos) é um sistema de arquivos que gerencia o acesso a arquivos em HDs e outras mídias. Criado em 1996 pela Microsoft para substituir o FAT16 usado pelo MS-DOS e com uma série de limitações. O FAT32 foi implementado nos sistemas Windows 95 (OSR2), Windows 98 e Millennium e ainda possui compatibilidade com os sistemas Windows 2000 e Windows XP, que utilizam um sistema de arquivos mais moderno, o NTFS, que foi continuado, sendo usado também nos sistemas Windows Vista, Windows 7 e Windows Server 2008 R1/R2 (para servidores empresariais).


3 - ***EXT4***\

O primeiro sistema de arquivos suportado pelo Linux foi o Minix. Ele apresentava alguns problemas de desempenho significativos e, assim, foi criado outro sistema de arquivos, especificamente para o Linux, denominado sistema de arquivos estendido. O primeiro sistema de arquivos estendido (ext) foi projetado por Remy Card e introduzido no Linux em abril de 1992. O sistema de arquivos ext foi o primeiro a utilizar o comutador do Sistema de Arquivo Virtual (VFS) implementado no kernel 0.96c e suportava sistemas de arquivos de até 2 gigabytes (GB). 

O Ext4 [3] apresenta inúmeros novos aprimoramentos quanto a desempenho, escalabilidade e confiabilidade. Mais especificamente, o ext4 suporta sistemas de arquivos de 1 exabyte. Ele foi implementado por uma equipe de desenvolvedores, liderados por Theodore Tso (responsável pela manutenção do ext3) e introduzido no kernel 2.6.19. Encontra-se agora estável no kernel 2.6.28 (desde dezembro de 2008). 

O ext4 pega emprestado vários conceitos úteis de muitos sistemas de arquivos concorrentes. Por exemplo, a abordagem baseada em extensões para o gerenciamento de blocos foi implementada no JFS. Outro recurso relativo ao gerenciamento de blocos (alocação com atraso) foi implementado tanto no XFS quanto no ZFS da Sun Microsystems.


Com bases nos sistemas de arquivos citados, esse trabalho visa uma análise
envolvendo as seguintes operações: 

- Operação de criação de arquivos;
- Operação de leitura de arquivos;
- Operação de destruição de arquivos; 

Para arquivos com tamanhos de:
- 5Kb
- 10Kb
- 100Kb
- 1Mb
- 10Mb
- 100Mb
- 500MB

O comando **dd** são as iniciais de Data Definition, é um utilitário de linha de comando que em primeiro lugar, tem como principal função converter e copiar arquivos. Esse programa foi utilizado para gerar os respectivos arquivos em um determinado path.


````
dd if=/dev/zero of=/media/linux/device/file.img bs=5k count=1
````
Onde **if** é origem do arquivo, **of** o destino, **bs** é o tamanho do bloco, e **count** a quantidade de blocos. Aproveitando os isumos do primeiro módulo, utilizamos o comando **time** para aferir o tempo de leitura e destruição dos arquivos.

Como a linguagem de programação  não foi especificada, utilizamos o Shell do prompt de comando para fazer o loop de execução.

O nosso código executa um loop que escreve, le e remove, de forma automática. Executando todas as rotinas de forma programada e com extrema consistência entre as execuções.


***Análise dos Dados***
-------------------

Foram realizadas várias rodadas de testes com cada tipo de sistema de arquivos. A tabela abaixo mostra os valores coletados dos testes, esses valores foram sumarizados em média e desvio padrão. Cada experimento teve pelo menos, 40 rodadas de execução para cada um dos cenários apresentados.


![stats](/assets/tabelas/ext4.png)
**Tabela 1 - Tabela de dados do sistema de arquivos EXT4**

![stats](/assets/tabelas/fat32.png)
**Tabela 2 - Tabela de dados do sistema de arquivos FAT32**

![stats](/assets/tabelas/ntfs.png)
**Tabela 3 - Tabela de dados do sistema de arquivos NTFS**


Com base nas Tabelas 1, 2 e 3, foram gerados alguns gráficos, com a finalidade de comparar os tipos de operações e os tamanhos dos arquivos manipulados por cada sistema.

![stats](/assets/graficos/EXT4.png)\
**Grafico 1 - Gráfico comparativo das operações do sistema de arquivos EXT4**

![stats](/assets/graficos/FAT32.png)\
**Grafico 2 - Gráfico comparativo das operações do sistema de arquivos FAT32**

![stats](/assets/graficos/NTFS.png)\
**Grafico 3 - Gráfico comparativo das operações do sistema de arquivos NTFS**


Nota-se que, em todos os casos, conforme esperado, quanto maior a arquivo que a operacao tinha que manipular, maior seria o tempo. Porém todos os sistemas de arquivos tem uma boa performance até arquivos de 100M. A partir desses valores, os tempos de operação são de ordem exponenciais. O desvio padrão tambem tende a ser maior entre as operações com arquivos maiores, pelo fato dessas operacoes levarem mais tempo, os recursos da máquina, bem como o sistema operacional, precisam lidar com outras operações que ocorrem de forma concorrente no sistema, o que explica um aumento considerável no tempo para operações com arquivos maiores que 10M.


Referências
-------------------
1. http://dubeyko.com/development/FileSystems/NTFS/ntfsdoc.pdf
2. http://read.pudn.com/downloads77/ebook/294884/FAT32
3. https://www.kernel.org/doc/html/latest/filesystems/ext4/index.html

Contatos 
-------------------
antonio.alessandro@usp.br\
diegopedroso@usp.br
