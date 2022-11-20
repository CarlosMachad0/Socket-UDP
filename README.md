# Socket-UDP
Calculation of Jitter and Round trip time

Primeiro exercício: 

Desenvolve um software em C que recebendo como argumento a porta cria um socket UDP e fica a escuta de dados. Ao receber um pacote no socket em causa envia outro de resposta para o cliente que originou o pacote de receção.
Ao mesmo tempo recolhe dados de jitter entre os vários pacotes que recebeu.
Ao receber o sinal de CTRL + C para sair intercepta e imprime as estatísticas antes de sair.

As estatísticas de Jitter esperadas são as seguintes:

Número de pacotes recebidos
Jitter mínimo
Jitter médio
Jitter máximo
Delta entre o primeiro pacote e o ultimo.
Segundo exercício:

Desenvolve um software em C que recebendo como argumentos o endereço IP e porta cria um socket UDP e começa a enviar pacotes para o endereço e porta fornecidos.
Envia os pacotes com um delta de 100 milissegundos (o mais preciso que conseguires).
Ao receber pacotes de volta recolhe dados de round trip time.

Ao fim de 100 pacotes imprime as estatísticas e sai.

As estatísticas de round trip time esperadas são:

Número de pacotes enviados
Número de pacotes recebidos
Round trip time mínimo
Round trip time medio
Round trip time máximo
Delta entre o primeiro pacote enviado e o ultimo enviado.

