
# Projeto de Lab Prog I

O projeto é um jogo baseado no antigo jogo Spacewar (1962).

## Índice
1. [Instalar](#instalar)
  1. [UNIX](#sistemas-unix-based)
2. [Como jogar](#como-jogar)
3. [Dependências](#dependências)
4. [Sobre o Código](#sobre-o-código)
  1. [Primeira Entrega](#v01)
  2. [Segunda Entrega](#v02)
    1. [Sobre a SDL](#sobre-a-sdl)
5. [Créditos](#créditos)


## Instalar

### Sistemas UNIX-based

Para compilar, use o **cmake** na pasta raíz do projeto.
É recomendado que se crie uma pasta build e dentro dela se use o comando `cmake ..`
Depois, basta usar o `make` na pasta onde foi executado o cmake.
Se preferir, tudo resumido (em bash) em uma só linha, a partir da pasta raíz:
```bash
mkdir build; cd build; cmake ..; make
```

O arquivo binário será criado numa subpasta `bin` com o nome `SpaceCats`. Junto dele estará
um arquivo texto `inputdata`, que contém os parâmetros de entrada padrão do jogo, e a pasta de assets. Você pode também dar `cmake` e `make` direto da pasta raíz, mas vai ficar tudo bagunçado.

## Como jogar

A partir da v0.3 o jogo agora lê um arquivo de configuraçã sozinho e não precisa receber uma entrada padrão. Isso deixa a execução do jogo mais fácil para o usuário. Basta abrir o executável que o jogo já roda. Pelo bash você pode rodar algo assim:
```bash
./bin/game
```

A nave `grumpy_cat` é controlada pelas setas direcionais. A nave `nyan_cat` é controlada pelas teclas WASD. Os botões `shift` atiram, cada um com um nave diferente.

## Dependências

Para compilar, você vai precisar de [cmake](https://cmake.org),
[make](https://www.gnu.org/software/make/),
um [compilador C](https://gcc.gnu.org/), e
[SDL2, SDL2_image e SDL2_ttf](https://www.libsdl.org/) instalados no seu computador.

## Sobre o Código


### v0.1
**(Primeira entrega)**

O jogo tem três tipos de elementos, organizados em structs: Planet, Ship, e Bullet. Eles são instanciados em uma struct global chamada Game para maior facilidade de acesso. Esses elementos são inicializados em uma função `load()`, que pega a entrada padrão e a transforma em parâmetros para os "construtores" dos elementos.

O programa atualiza a lógica e a física na função `update()` a uma taxa de _x quadros por segundo_, sendo x o número equivalente ao primeiro parâmetro recebido pelo programa em `argv`. A cada atualização as naves (Ship) e os tiros (Bullet) são coagidos por forças gravitacionais com os outros elementos vivos no jogo. E assim se movem somando à suas posições as velocidades calculadas a partir das acelerações geradas por essas forças.

No entanto, as forças não são explicitadas no código. Em vez disso, somam-se as acelerações componentes à velocidade. Essa acelerações são calculadas através das forças gravitacionais individualmente. Em outras palavras, assumimos que:
```
F = m * a => a = F/m => (a_1 + ... + a_n) = (f_1 + ... + f_n)/m
```
E, portanto, não precisamos calcular F (resultante) para saber a aceleração resultante. Melhor ainda, nem calculamos a aceleração resultante explicitamente, apenas somamos suas componentes na velocidade a cada atualização de lógica do jogo, e assim obtemos o mesmo resultado.

Os valores constantes, como as massas e a constante gravitacional, devem ser devidamente ajustados quando tivermos uma simulação visual. Por enquanto, estão sendo utilizado valores arbitrários, respeitanto apenas:
```
massa_planeta > massa_nave > massa_tiro
```

### v0.2
**(Segunda entrega)**

A partir dessa versão, o jogo utiliza a biblioteca SDL para suporte gráfico e interativo.
Para isso, mudamos o modo de compilação para utilizar `cmake` em vez de apenas `make`.
Isso serviu para gerar maior compatiblidade entre sistemas operacionais na hora de incluir
os headers de SDL, SDL_image e SDL_ttf.

Mudamos o nome da struct Game para Elements. Já que a struct apenas guardava elementos do jogo, e as configurações do jogo são guardadas em outras struct, decidiu-se que Elements melhor representava o que a struct armazena. Isso também melhorou a nomenclatura dos arquivos, e permitiu melhor modularização. Agora, a struct Elements tem funções próprias para inicializar os seus elementos, e gerenciá-los melhor. O código em game.c irá se preocupar agora em cuidar dos diferentes módulos do jogo, e não seus elementos.

Houve significativo uso de _pools_ nessa etapa de código. As bullets foram inicialmente postas em um único vetor para funcionarem como elementos de um _pool_, mas seu comportamento como tal não foi programado na etapa anterior. Agora, há diversos _pools_ no jogo. Timers, Texboxes, Sprites e DrawPos, são todos _structs_ que usam _pools_ para serem armazenados. Isso cria certo dinamismo para esses elementos, uma vez que futuramente podem ser criados e deletados dinamicamente. A presença de _pools_ para cuidar dessa dinâmica evita o alocamento de memória de maneira fragmentada.

Também resolvemos alterar um pouco o funcionamento da física. Na primeira etapa, colocamos valores bem arbitrários de constante gravitacional, massa e posição, justamente por não termos _feedback_ visual sobre o que eles significavam no jogo. Agora que colocamos gráficos e textos e um pouco de interação, conseguimos equilibrar um pouco melhor a movimentação dos corpos físicos no espaço do jogo. Uma ressalva importante é que criamos uma "resistência do ar" no espaço, o que fisicamente não faz sentido nenhum, mas melhora incrivelmente a jogabilidade do jogo. Literalmente não dá pra jogá-lo sem essa "resistência", pois sem ela as velocidades facilmente extrapolam a escala do mapa do jogo. Pode ser uma força errada e que não existe no vácuo, mas sua presença torna o jogo mais interessante e jogável. Se quiser fazer o teste, sinta-se a vontade para comentar a função `void Physics_slowdown(Physics *body)`, e ver como os elementos chovem na tela de tão rápidos que ficam.

Note que se você comentar a função `void Physics_slowdown(Physics *body)`, e setar calcular os parâmetros dos corpos para obedecer a equação abaixo, os corpos entraram em órbita.
```
v^2 = G * M / R
```
Sendo v o módulo da velocidade perpendicular ao raio, G a constante gravitacional declarada em `physics.c`, M a massa do planeta, e R a distância do corpo ao centro do planeta.

#### Sobre a SDL

Resolvemos utilizar a biblioteca SDL, que é um _wrapper_ do OpenGL, semelhantemente ao GLUT, pois acreditamos que sua documentação seria melhor, assim como também resultaria em maior facilidade de uso. Fora isso, é uma biblioteca feita para desenvolvimento de jogos, e é largamente utilizada nessa indústria. Ela possui diversos módulos e submódulos, como a SDL_image e a SDL_ttf, que servem para carregar imagens e fontes com maior suporte a diferentes formatos de arquivo.

Ela precisa ser inicializada, e seus elementos alocados. Criamos dois módulos que cuidam disso: o Events e o Graphics. O módulo Events cuida de inputs e suas consequências na lógica do jogo. Também criamos um elemento Controllers, que mapeia quais inputs fazem o quê em determinado estado de jogo. Já o módulo Graphics cuida da janela, do renderer, e das imagens e textos desenhados neles. Ao terminar o jogo por input (seja fechando a janela com o botão x/botão vermelho no seu canto superior, seja apertando o botão `escape` (**retirado na versão 0.3**), seja apertando `ctrl+c` no terminal que o executou), os módulos liberam os elementos da SDL que precisaram ser alocados.

Curiosamente o valgrind aponta a SDL como causa de vazamento de 230bytes. Gostaríamos de assegurar que não temos como evitar que isso aconteça, pois não sabemos o que a SDL faz no seu código para causar tal vazamento. Agradecemos a compreensão.

### v0.3
**(Terceira entrega)**

Jogamos tudo fora e começamos de novo. Brinks, na verdade reorganizamos o código para ser mais consistente em sua arquitetura. Agora todas as instâncias dentro do jogo tem suas próprias _pools_ e compartimentalizam as suas instâncias.
Isso significa que apenas um módulo consegue ver diretamente suas instâncias. Outros módulos, para acessarem informações externas, tem que chamar métodos dos outros módulos para tal. Por exemplo, uma instância do componente do tipo Sprite precisa de informação de uma instância do componente do tipo DrawPos para poder renderizar uma imagem na tela. Em vez de acessar diretamente a informação, o componente Sprite guarda em si um ID de uma instância de um componente DrawPos, e passa esse ID como parâmetro de uma função do gerenciador de componentes DrawPos para receber a informação que precisa (no caso a posição da imagem na janela).

Outra coisa que fizemos é **destruir tipos de elementos**. Agora os elementos, renomeados como _entidades_, são compostos de **componentes**. Os componentes são o _Model_ do programa (traçando paralelo com a arquitetura de código _MVC_). Uma entidade se comporta de um jeito ou de outro de acordo com os componentes que possui. _Assim, entidades não tem tipo._

Também criamos **Ações**. Ações são um pequeno módulo que servem para atuar sobre os componentes de certas entidades. Elas são basicamente listas de entidades que guardam quais destas sofrerão uma ação. Existe uma lista de entidades para cada ação, que pega os componentes dessas entidades e os modificam de alguma forma. As ações podem ser contínuas ou pontuais. Uma ação contínua, por exemplo, é a chamada do cálculo de gravidade. Uma ação pontual, por exemplo, é uma nave atirar um projétil. Uma ação contínua não se preocupa em tirar a entidade da sua lista. Uma ação pontual, após executar seu código, retira a entidade de sua lista. Elas funcionam como o _Controller_ do programa (de novo, da arquitetura _MVC_, mas não deve ser confundido com os **controllers de input** do programa).

Também implementamos _features novas_:

1. Colisão. As coisas colidem, morrem e explodem.
2. Atirar. As naves atiram agora com o shift mais próximo do direcional usado (LSHIFT para controle WASD, RSHIFT para controle nos direcionais).
3. Executar o programa é mais fácil. O antigo arquivo de entrada padrão agora é um arquivo de configuração. Ele é mais legível e não precisa ser passado como entrada padrão, o código se encarrega de o encontrar e o interpretar. Então é possível rodar o jogo apenas executando seu binário (contanto que você não tire os outros arquivos de leitura da pasta do binário, pois eles são importantes para sua execução).

## Créditos

**MAC0211 Laboratório de Programação I**

**Grupo:**
* André Victor Nakazawa (9298336)
* Isabela Blucher (9298170)
* Willian Akira Mizutani (8010041)

O código aqui exposto é de nossa autoria, com exceção dos arquivos de configuração na pasta `cmake`, que são de autoria de [Brendan Whitfield](https://github.com/brendan-w) (saiba mais sobre seu projeto [collector](https://github.com/brendan-w/collector) e sua [licença](https://github.com/brendan-w/collector/blob/master/LICENSE).

As imagens foram feitas por Willian Akira Mizutani, e estão sob a licença [Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License](http://creativecommons.org/licenses/by-nc-sa/4.0/). Grumpy Cat® pertence a Tabatha & Bryan Bundesen, e Nyan Cat® pertence a Christopher Torres. As imagens representadas nesse jogo não possuem intenção comercial, e sim de uso acadêmico e paródico, e portanto não infringem leis de copyright dessas marcas.

Para informações sobre a licença deste nosso projeto, leia o nosso arquivo [LICENSE](https://github.com/OrenjiAkira/spacegame/master/LICENSE).

Para o uso da biblioteca SDL, utilizamos o tutorial do site [Lazy Foo](http://lazyfoo.net/tutorials/SDL/).

Também utilizamos de referência o livro [Game Programming Patterns](http://gameprogrammingpatterns.com/) de Robert Nystrom.
