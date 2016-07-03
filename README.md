
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
  3. [Terceira Entrega](#v03)
  4. [Quarta Entrega](#v04)
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
um arquivo texto `data`, que contém os parâmetros de entrada padrão do jogo, e a pasta de assets. Você pode também dar `cmake` e `make` direto da pasta raíz, mas vai ficar tudo bagunçado.

Se passar para o cmake o parâmetro `-DDEBUG_MODE=TRUE` prints de log serão ativados durante a execução do programa.
Se quiser desativar os prints depois de ter rodado o cmake com o argumento de debug, basta rodar o cmake com `-DDEBUG_MODE=FALSE`, e recompilar com o `make`.

Um outro parâmeto que você pode passar para o cmake é `-DNO_MUSIC=TRUE`. Isso faz o jogo rodar sem música de fundo. A música causa um bug em sistemas Mac OSX, e por isso essa flag foi criada. Se estiver tendo problemas para rodar o jogo com música, experimente usar essa flag. De novo, para desativar a flag, basta rodar de novo o cmake com a flag `-DNO_MUSIC=FALSE`.

Se estiver com preguiça, como a gente, basta usar o script bash novo [da versão 0.4](#v04):
```bash
./compile [parâmetros]
```
Ele está na pasta raíz do repositório, e gerencia as flags para você. Basta passar, ou não, os parâmetros `--debug` e `--no-music`. Se passar, essas flags acima viram `TRUE`, se não, viram `FALSE`.


## Como jogar

A partir da v0.3 o jogo agora lê um arquivo de configuração sozinho e não precisa receber uma entrada padrão. Isso deixa a execução do jogo mais fácil para o usuário. Basta abrir o executável que o jogo já roda. Pelo bash você pode rodar algo assim:
```bash
./build/bin/SpaceCats
```

Os controles são visíveis na cena de escolher personagem. O PLAYER 1 controla a nave com os botões WASD, e atira com SPACE e LSHIFT. O PLAYER 2 controla a nave com os direcionais, e atira com ENTER e RSHIFT.

## Dependências

Para compilar, você vai precisar de [cmake](https://cmake.org),
[make](https://www.gnu.org/software/make/),
um [compilador C](https://gcc.gnu.org/), e
[SDL2, SDL2_image, SDL2_ttf, e SDL2_mixer](https://www.libsdl.org/) instalados no seu computador.

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

Também criamos **Ações**. Ações são um pequeno módulo que serve para atuar sobre os componentes de certas entidades. Elas são basicamente listas de entidades que guardam quais destas sofrerão uma ação. Existe uma lista de entidades para cada ação, que pega os componentes dessas entidades e os modificam de alguma forma. As ações podem ser contínuas ou pontuais. Uma ação contínua, por exemplo, é a chamada do cálculo de gravidade. Uma ação pontual, por exemplo, é uma nave atirar um projétil. Uma ação contínua não se preocupa em tirar a entidade da sua lista. Uma ação pontual, após executar seu código, retira a entidade de sua lista. Elas funcionam como o _Controller_ do programa (de novo, da arquitetura _MVC_, mas não deve ser confundido com os **controllers de input** do programa).

Também implementamos _features novas_:

1. **Colisão.** As coisas colidem, morrem e explodem.
2. **Atirar.** As naves atiram agora com o shift mais próximo do direcional usado (LSHIFT para controle WASD, RSHIFT para controle nos direcionais).
3. **Executar o programa é mais fácil.** O antigo arquivo de entrada padrão agora é um arquivo de configuração. Ele é mais legível e não precisa ser passado como entrada padrão, o código se encarrega de o encontrar e o interpretar. Então é possível rodar o jogo apenas executando seu binário (contanto que você não tire os outros arquivos de leitura da pasta do binário, pois eles são importantes para sua execução).

**Nota sobre memória:** usamos memória estática para a maioria das coisas, por questão de eficiência. As _pools_ são vetores de tamanho fixo, em geral de 256. Ou seja, assumindo a presença de duas naves, uma imagem de fundo, e um planeta no centro (ou seja, um total de 4 entidades), acreditamos ser humanamente impossível você atirar bullets o suficiente para criar mais que 252 outras entidades (em menos tempo que demora para elas morrerem sozinhas) e estourar a memória do jogo. As bullets apenas são criadas no evento do usuário pressionar a tecla de tiro, mas não no evento do usuário segurar a tecla, o que torna 60 tiros por segundo, na prática, impossível. Mesmo que isso ocorra, o jogo apenas dirá que a _pool_ estourou e vai fechar o programa de maneira correta, liberando as memórias que alocou.

Ainda na nota sobre memória, a SDL ainda vaza uns 200 bytes de memória, mesmo fechando seus módulos de maneira correta. De novo, isso é culpa de sua implementação interna, fora de nosso controle. Pelo menos o valor é fixo.

### v0.4
**(Quarta entrega)**

As mais recentes atualizações incluem SOM! Sim, som! Temos efeitos sonoros e adicionamos a biblioteca SDL_mixer, também parte da SDL. Tudo bem que no espaço o som não se propaga, mas quem se importa? É legal, dá feedback pro jogador, é _juicy_. Adicionamos uma música ambiente também, porém, ao menos em sistemas Mac OSX, ao tocá-la acontece, de maneira inconsistente, um _segmentation fault_. Inconsistente, sim. Logo, a culpa não é nossa. Adicionamos uma flag de compilação para o jogo não tocar a música, o que não é ideal. Se ocorrer esse bug para você usando outro sistema operacional, você pode submeter uma issue, ou mandar email pra gente mesmo.

Fora isso, melhoramos o sistema de cenas, e criamos macros para gerar os controles para a gente. Os arquivos de `controllers` ficaram bem menores, e as cenas agora cuidam de fazer a interação de maneira mais complexa. Por exemplo, agora temos uma tela de "Choose your ~~character~~ cat", na qual cada jogador pode escolher com que gato irá jogar! Legal, né?

E ah, sim, melhorias na compilação. Criar uma pasta build é muito chato e repetitivo. Fizemos um script em bash para isso. Claro, ainda funciona compilar do mesmo jeito (`cmake` + `make`), mas agora você pode compilar com um só comando `./compile`. Ele já cria a pasta e compila as coisas lá. Ele também aceita flags de compilação. Dá uma olhada na seção [Instalar](#instalar).

## Créditos

**MAC0211 Laboratório de Programação I**

**Grupo:**
* André Victor Nakazawa (9298336)
* Isabela Blucher (9298170)
* Willian Akira Mizutani (8010041)

O código aqui exposto é de nossa autoria, com exceção dos arquivos de configuração na pasta `cmake`, que são de módulos de cmake de feitos específicos para a SDL2 e seus submódulos. Ver licenças nos próprios arquivos.

As imagens foram feitas por Willian Akira Mizutani, e estão sob a licença [Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License](http://creativecommons.org/licenses/by-nc-sa/4.0/). Grumpy Cat® pertence a Tabatha & Bryan Bundesen, e Nyan Cat® pertence a Christopher Torres. As imagens representadas nesse jogo não possuem intenção comercial, e sim de uso acadêmico e paródico, e portanto não infringem leis de copyright dessas marcas.

Os efeitos sonoros foram feitos por Willian Akira Mizutani, e estão sob a licença [CC0 1.0 Universal (CC0 1.0) Public Domain Dedication](https://creativecommons.org/publicdomain/zero/1.0/). A trilha sonora foi feita por ["Jordan"](http://opengameart.org/users/joth) e está sob a [mesma licença](https://creativecommons.org/publicdomain/zero/1.0/).

Para informações sobre a licença deste nosso projeto, leia o nosso arquivo [LICENSE](https://github.com/OrenjiAkira/spacegame/master/LICENSE).

Para o uso da biblioteca SDL, utilizamos o tutorial do site [Lazy Foo](http://lazyfoo.net/tutorials/SDL/).

Também utilizamos de referência o livro [Game Programming Patterns](http://gameprogrammingpatterns.com/) de Robert Nystrom.
