# Shift-Registration-Application

## Introdução
Pretende-se desenvolver uma aplicação que permita fazer a inscrição de alunos de um UC nos respectivos turnos. A aplicação processa de forma independente turnos teóricos e práticos e ignora completamente os horários.
Os turnos são identificados por um nome e é necessário especificar a capacidade de cada um. A aplicação necessita também da lista de alunos inscritos na UC, para validação das marcações e detecção de estatutos prioritários (i.e., estudantes-trabalhadores e portadores de deficiência).
Um ciclo de utilização da aplicação compreende 3 fases diferentes:
- Configuração – fase inicial em que se inserem os turnos e alunos inscritos
- Marcação – período em que os alunos podem indicar as suas preferências por turnos
- Geração – fase final em que são produzidas as listas de alunos colocados em cada turno
Devido à eventual extinção e/ou a alteração das vagas dos turnos, a aplicação poderá ser utilizada para repetir a geração dos turnos da mesma UC sem perda dos dados das marcações anteriores.

## Requisitos
### Funcionais:
1. Os dados de entrada são:
    - Lista de alunos inscritos na UC
    - Lista de turnos, com respectivo nome e número de vagas
    - Preferências dos alunos pelos turnos (ordenação dos turnos), etiquetadas temporalmente.
2. Os dados de saída são as listagens ordenadas de alunos em cada turno, incluindo a indicação de alunos não inscritos, e alunos não colocados por falta de vagas. A ordem é a da data-hora das marcações.
3. Só permite realizar uma fase do ciclo de utilização se existirem os dados da fase anterior, e permite limpar todos os ficheiros de dados.
4. Cada aluno é colocado num só turno e, se se inscrever mais do que uma vez, conta a última marcação.
5. As vagas são ocupadas por ordem da marcação e da preferência. Os alunos com estatuto de estudante-trabalhadore e portador-de-deficiência têm prioridade, ou seja, colocados antes dos alunos com outros estatutos.
6. Na eventualidade de ser necessário repetir a geração de turnos:
    - Os alunos para os quais seja possível (colocados abaixo do novo limite), podem congelar previamente a sua colocação.
    - Todos os alunos podem alterar a sua marcação, ficando a contar a nova data-hora.
### Não funcionais:
- O código deve ser estruturado de forma orientada-aos-objectos.
- As informações que necessitem de ser persistentes devem ser guardadas em ficheiros.
- O formato dos ficheiros de entrada e saída deve ser compatível com o Excel.

## Plano
A aplicação será desenvolvida em duas versões:
- Uma tradicional aplicação consola (tarefas 1 a 4).
- Um serviço web e um conjunto de páginas HTML estáticas simples que permitam aos utilizadores interagirem com o serviço (tarefas 5 e 6).
### 1. Configuração
Definir o formato dos ficheiros de configuração com os turnos e alunos inscritos.
Leitura dos 2 ficheiros, validação do formato e carregamento da informação em estruturas de dados adequadas.
Implementação de uma interface simples que permita receber os ficheiros e fornecer um sumário final, no mínimo com o número de turnos e alunos.
Gravação dos dados em 2 ficheiros próprios da aplicação para validação. O formato pode/deve ser o mesmo do input.
### 2. Marcações
Implementar a recepção de marcações utilizando uma interface que deve ser o mais simples possivel. Esta interface deve permitir inserir marcações individuais e em lote (através da indicação de um ficheiro).
Estudar a API da biblioteca padrão C++ para tratar e representar data-e-hora. Na marcação individual é o programa que coloca a etiqueta temporal em tempo-real.
Validar cada marcação comparando com os dados dos alunos inscritos e mostrar na consola o resultado:
• Na marcação individual
o se for inválida, uma mensagem descritiva do erro;
o se for de um aluno prioritário, indicar/confirmar o turno em que ficou colocado (assumir estes alunos cabem nos turnos da sua primeira preferência);
o senão, confirmar a recepção da marcação.
• Na marcação em lote
o para cada inscrição, se for inválida, uma mensagem descritiva do erro;
o um sumário final, no mínimo com o número de inscrições correctas.
Guardar os dados das marcações válidas em ficheiro, para permitir a repetição do ciclo de inscrição. O formato pode/deve ser o mesmo da marcação em lote.
### 3. Estruturação Orientada-aos-Objectos
Concepção do conjunto de classes da aplicação, seguindo os princípios e práticas que têm sido leccionadas. É valorizada a utilização adequada de polimorfismo e padrões de desenho.
Descrição na forma de um diagrama de classes UML, incluindo as variáveis e funções membro de cada classe.
Mover o código já desenvolvido para a estrutura de classes escolhida, fazendo as necessárias alterações. O código deve compilar e executar tal como nas fases anteriores.
### 4. Geração de turnos
Definir o formato dos ficheiros com a constituição dos turnos.
Implementação do que falta das classes concebidas na fase anterior, incluindo o algoritmo de geração dos turnos. Num programa orientado a objectos é normal que um algoritmo envolva (esteja distribuído por) várias classes/objectos.
Descrição do algoritmo de geração dos turnos num diagrama de actividades. Experimentar a importação/abertura do ficheiros gerados no Excel.
### 5. Serviço web e respectivos pedidos
Instalação do servidor HTTP e configuração de acordo com a tecnologia web a utilizar.
Estudo da tecnologia web utilizada para implementar o serviço, incluindo os principais aspectos do protocolo HTTP e HTML básico.
Definição dos pedidos HTTP que o serviço suportará:
- configurar os alunos inscritos
- configurar os turnos e vagas
- submeter inscrições em lote
- fazer a inscrição de um aluno
- consultar a inscrição de um aluno
- alterar a inscrição de um aluno
- obter os turnos
- congelar a colocação no turno atribuído
- eliminar os dados armazenados
Implementação de um serviço que receba os referidos pedidos e forneça uma resposta de sucesso para os pediso válidos e de erro nos outros casos. Teste do serviço utilizando uma ferramenta como o Postman ou utilizando páginas HTML.
### 6. Cliente web e respostas do serviço
Migração da parte lógica do código da aplicação consola para o serviço web e testes de validação através dos ficheiros produzidos.
Estudo da linguagem HTML orientado para os elementos que permitam a construção de páginas simples para as 3 fases do ciclo de utiliação da aplicação: configuração, marcações e geração de turnos.
Implementação das páginas de interacção com serviço web, nomeadamente gerando os pedidos HTTP definidos na tarefa anterior.
Implementação das respostas do serviço aos pedidos definidos na tarefa anterior, produzindo uma página HTML com o(s) resultado(s) do respectivo pedido. Pela sua importância, destacam-se as seguintes respostas aos pedidos:
- sucesso (e o turno ocupado no caso de aluno prioritário) ou insucesso da marcação
- dados da marcação feita anteriormente e as opções de alterá-la ou congelar o turno atribuído
- listagem dos turnos gerados ou download de ficheiro zip respectivo, consoante a opção escolhida no pedido.
É de realçar também que a página de resposta ao pedido 5 é a que permite a realização dos pedidos 6 e 8, ou seja, os pedidos 6 e 8 não têm uma página HTML estática (i.e., ficheiro) respectiva.

## Avaliação
O projecto será avaliado de acordo com as seguintes componentes:
- Cumprimento de requisitos
- Cumprimento das datas de entrega
- Qualidade do software, nomeadamente:
- classes devidamente encapsuladas
- dependências entre classes reduzidas
- distribuição coerente e equilibrada das funcionalidades, ou seja, respectivamente, funções com relações estreitas devem estar juntas e classes não devem ser demasiado grandes.


---
---

## Requisitos
### Fase 1 - Configuração dos Turnos e dos Alunos inscritos na UC

- No mínimo, cada aluno deve possuir um nome e um número mecanográfico.
- O nome não pode conter dígitos e o número mecanográfico não pode conter outra coisa que dígitos.
- O Estatuto Especial, como o próprio nome indica, pode não existir, contudo, se existir, terá de ser um EE válido:
      - TE (Trabalhador Estudante);
      - AAC (Atleta de Alta Competição);
      - PDEF (Portador de Deficiência);
      - DAE (Dirigente Associativo);
      - DLG (???)
- No que toca à configuração dos Alunos inscritos na UC, este pode ser realizado por 2 formas:
      - Em Lote, onde é recebido um ficheiro com os alunos inscritos na UC;
      - Manualmente, onde oferece a possibilidade de adicionar um Aluno à UC em questão.
- Todos estes dados são sujeitos a um processo rigoroso de validação, em que são detetados todos os erros ocorrentes e indicando, no caso
  dos ficheiros, a(s) linha(s) em que esses erros ocorreram, bem como o motivo dos mesmos.
- São casos de erros:
      - Inválida Sintaxe do ficheiro;
      - Falta de algum campo obrigatório (nome ou número mecanográfico);
      - Nome e Número mecanográfico inválidos;
      - Estatuto Especial inválido;
      - Aluno repetido;
      - ...
- No final de processar toda esta informação, caso o ficheiro estiver corretamente formatado e sem nenhuma anomalia, é emitida uma mensagem de sucesso e o registo dos 
  alunos na UC é realizado.
  Caso exista algum tipo de anomalia/erro, são reportados todos os eventuais erros de forma a tornar o sistema o mais seguro possível e permitindo ao Docente verificar as
  anomalias ocorrentes, bem como a linha em que ocorreu.
- No que concerne à configuração dos Turnos, estes podem ser configurados de forma:
      - Automática, isto é, recebendo um ficheiro com todos os turnos (Nome e Número de vagas);
      - Manual, onde podemos definir o número de turnos, nome e número de vagas disponíveis para cada Turno
- Todos estes dados são devidamente verificados, nomeadamente a sintaxe do ficheiro recebido, a existência de turnos com vagas vazias, com números negativos ...
  Nota: O nome dos turnos não é obrigatório, por defeito, assumimos PL1, PL2, PL3 ... , consoante o número de turnos.
- Outras funcionalidades extras:
      - Possibilidade de remover um Aluno da lista de Alunos da UC;
      - Possibilidade de encontrar/saber se um determinado Aluno consta na Lista de Inscritos na UC;
      - Possibilidade de consultar o estado das Inscrições (Número de Alunos inscritos e informações dos turnos);
      - Aviso Automático no que toca à possibilidade da quantidade dos Alunos inscritos já na UC ser superior às vagas totais dos turnos;
      - Possibilidade de retomar as Inscrições a qualquer momento;
      - Possibilidade de dar reset e começar um novo ciclo de Inscrições


### Fase 2 - Marcações

- Etapa responsável pela marcação dos alunos da UC em questão (configurados na Fase 1), nos turnos, também estes configurados na Fase 1
- Possibilidade de o utilizador escolher entre os dois modos (Configuração ou Marcação)
- Ao entrar no menu que diz respeito às marcações, tem de obrigatoriamente:
      - Ter alunos inscritos na UC;
      - Ter turnos configurados;
      - O número de Vagas totais nos turnos ser superior ou igual ao número de alunos inscritos na UC;
- Todos os erros descritos acima são reportados ao utilizador de modo a tornar o programa o mais mais interativo e seguro possível.
- Outro aspeto importante é que, quando escolhido o modo 2 (Marcações), o utlizador não poderá voltar a alterar nas configurações da UC, isto é, quando feita alguma marcação, 
  o utilizador não poderá mudar os registos da UC, podendo comprometer todo o programa.
- No que diz respeito às marcações propriamente ditas, estas podem ser realizadas de duas formas:
      - Em lote, em que é recebido um ficheiro com a data, número, nome e as preferências de cada aluno listado no ficheiro;
      - Manual, em que cada utilizador poderá realizar a sua inscrição manualmente.
- Todos estes dados são sujeitos a um processo rigoroso de validação, em que são detetados todos os erros ocorrentes e indicando, no caso
  dos ficheiros, a(s) linha(s) em que esses erros ocorreram, bem como o motivo dos mesmos.
- São casos de erros:
      - Inválida Sintaxe do ficheiro;
      - Falta de algum campo;
      - Data inexistente/mal formatada;
      - Aluno que não consta no registo de alunos da UC;
      - Preferências/nomes dos turnos incorretos;
      - ...
- Todas as marcações possuem algum tipo de feedback, podendo estas ser mensagens de erro/anomalia (como descritas acima), ou de sucesso.
- No caso de uma marcação ser efetuada com sucesso, esta pode possuir duas formas distintas:
      - Um aluno não prioritário realizou uma marcação (ou via ficheiro) corretamente e confirma-mos a marcação em questão;
      - Um aluno prioritário realizou uma marcação (ou via ficheiro) corretamente e confirma-mos o turno que ficou colocado
- Todas estas marcações são etiquetadas temporalmente, isto é, a cada inscrição (manualmente), é gerado a data correpondente à marcação;
- No caso de alunos que realizam mais que uma marcação, prevalece a última;
- Outras funcionalidades extras:
      - Possibilidade de remover um Aluno dos Turnos/Marcações;
      - Possibilidade de encontrar/saber se um Aluno consta nas Marcações ou se já está alojado num determinado Turno (Aluno Prioritário); 
      - Possibilidade de consultar o estado das Marcações (Número de Alunos já registados e número de alunos (prioritários) já alocados nos turnos);
      - Consulta em tempo real de quantas vagas ainda exitem, com os alunos prioritários já nos seus devidos turnos;
      - Possibilidade de retomar as Marcações;
      - Possibilidade de dar reset e começar um novo ciclo de Inscrições e Marcações


### Fase 3 - Geração dos Turnos

- Compreende-se por geração dos turnos o processo de integrar cada Aluno inscrito na UC (Fase 1) que efetuou uma inscrição válida (Fase 2) no respetivo Turno
- Quando o Docente escolher esta opção, é validado um conjunto de situações:
      - Só poderá entrar neste modo se efetuou as restantes etapas com sucesso;
      - Só poderá entrar neste modo se efetuou pelo menos uma Marcação com sucesso;
      - Aviso no que toca à possibilidade de iniciar o processo de geração dos turnos e ainda haver inscrições por fazer (Alunos registados na UC que não 
        fizeram a sua Marcação)
            - Oportunidade de Abortar a Geração de Turnos e por ventura inscrever/notificar os Alunos que ainda não fizeram a sua Marcação;
            - Oportunidade de iniciar o processo de Geração de Turnos
- No que concerne ao processo/algoritmo de geração de turnos, este é subdividido em duas partes:
      - Os alunos com estatuto especial têm prioridade face aos demais, ficando imediatamente colocados no respetivo Turno (feedback logo após a Marcação - Fase 2);
      - Alunos sem Estatuto Especial sujeitos a uma alocação temporal, isto é, aquando a marcação, estas são etiquetadas temporalmente (Fase 2). 
        Quando se dá inicio ao processo de gerar os turnos, prevalecem/possuem vantagem as marcações efetuadas temporalmente primeiro, e assim sucessivamente.
- É gerado os ficheiros correpondestes a cada Turno, bem como um ficheiro de Report de erros, indicando, por exemplo, que um determinado Aluno não ficou colocado
  no(s) turno(s) uma vez que já não havia vagas para o(s) mesmo(s).
- No final, todos os ficheiros previmanete carregados são apgados, de modo a poder começar uma nova sessão.
- Outras funcionalidades extas:
      - Possibilidade de escolher o diretório/pasta dos ficheiros gerados (Turnos + Report);
      - Aviso no que toca à possibilidade de algum aluno constar na lista da UC mas ainda não ter realizado a sua Marcação nos Turnos; 
      - Reset automático de forma a poder começar imediatamente um novo ciclo de Inscrições e Marcações para outra UC




