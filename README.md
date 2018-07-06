# DARPA
Entendido por Dispenser Automático de Remédios para pacientes com Alzheimer, ou apenas Dispenser de remédios, o DARPA, desenvolvido em Arduino com linguagem C, surgiu de um projeto da disciplina de sistemas embarcados no primeiro semestre de 2018. 

## A problemática
O Alzheimer é uma doença neuro-degenerativa que provoca o declínio das funções cognitivas, reduzindo as capacidades de trabalho e relação social e interferindo no comportamento e na personalidade da pessoa¹. Funções essas, relacionadas à memória e tendo como tratamento medicamentos como a rivastigmina, donepezil, etc. O esquecimento proveniente da doença que muitas vezes vêm aliado a um fator de risco como o envelhecimento é o grande problema quando se precisa ingerir quantidades relativamente grandes de remédios em um único dia. Organizá-los de forma correta torna-se uma tarefa complicada e exige que haja acompanhamento para evitar futuros problemas.

## O projeto
A ideia do protótipo é auxiliar quem precisa ingerir uma quantidade relativamente grande de remédios em um dia. Ao abastecer na parte superior e programá-lo, o despertador tocará no momento certo liberando e informando qual o medicamento na parte inferior. 

Na parte superior encontra-se todos os reservatórios para os remédios. A intenção não é separá-los por tipo, mas por horário. Caso o paciente precise ingerir mais de um tipo em um mesmo horário, deve-se inserir no mesmo local. Assim temos como controle os horários 1, 2, 3 e 4 de forma sequencial.

A programação dos horários e dos nomes dos remédios deve ser feita de forma manual (até então), basta que para isso seja conectado o cabo USB (na lateral - é necessário a instalação do Arduino e a modificação do código em algum computador).

Na parte frontal do protótipo observamos um botão MUTE. Caso o som emitido pelo despertador chegue a incomodar (o buzzer é tocado em dó, com frequência de 528 Hz, repetidas vezes por aproximadamente 1min e 30seg), basta que seja pressionado por 2 seg consecutivos e o mesmo cessará. O display, também observado na parte frontal, exibe a hora atual no formato HH:MM:SS e quando despertado é mostrado o nome do medicamento préprogramado. Por fim, em baixo se encontra a bandeja de destino da medicação.

Abaixo seguem os componentes do projeto:
* Arduino UNO
* RTC
* Motor de passo
* Buzzer
* Botão 4 pinos
* Display LCD 16x2
* Potenciômetro B10K
* Resistores de 220Ω e 1KΩ
* Protoboard
* Jumpers

## Os planos futuros
Não haveria sentido concluir o trabalho sem nenhuma forma de programá-lo de forma automática e mais simples. As pessoas que utilizariam o produto, precisariam de uma interface mediadora intuitiva e simples de ser acessada. A ideia para projetos futuros é desenvolver uma aplicação para Android e iOS para que com a conexão via Wi-Fi, seja simplificada essa tarefa. Com esta mesma aplicação o cuidador poderia acompanhar todos os despertadores tocados até então, auxiliando-o a conferir se o paciente realmente ingeriu o medicamento nas horas previstas. Para isso se faz necessário uma conexão de internet na casa do paciente e também, em termos de protótipo, acrescentar um módulo Wifi como o ESP8266.

## Referências
¹https://www.minhavida.com.br/saude/temas/alzheimer <Acessado em 06 de Jullho do 2018>
