# Modulacao_PWM

Este código controla um servomotor e um LED RGB usando PWM no Raspberry Pi Pico. O servomotor é movido suavemente entre 0° e 180° (e vice-versa), enquanto o LED RGB realiza um efeito de "fade" (desvanecimento) de brilho. A seguir, explico como o código funciona em detalhes:

### 1. **Configuração Inicial**:
   - **Servomotor (PWM)**:
     - O pino GPIO 22 é configurado para controle PWM para o servomotor.
     - O divisor de frequência (`SERVO_PWM_DIV`) e o valor de `SERVO_PWM_WRAP` são definidos para gerar uma frequência de 1 kHz e um período de 20 ms (padrão para servos).
     - O servomotor é controlado variando o ciclo de trabalho do PWM, onde o valor de `Servo_max` (2400 µs) corresponde à posição de 180°, `Servo_mid` (1470 µs) à posição de 90°, e `servo_max` (500 µs) à posição de 0°.
   
   - **LED RGB (PWM)**:
     - O pino GPIO 12 é configurado para controle PWM do LED RGB.
     - O divisor de frequência (`LED_PWM_DIV`) e o valor de `LED_PWM_WRAP` são configurados para uma frequência de aproximadamente 1 kHz e uma resolução de 8 bits (0 a 255) para o brilho.
     - O brilho do LED é ajustado alterando o ciclo de trabalho do PWM.

### 2. **Movimentação do Servomotor**:
   - O servomotor começa movendo-se para três posições diferentes, com pausas de 5 segundos em cada posição:
     - **180° (2400 µs)**: O servo é movido para 180°.
     - **90° (1470 µs)**: O servo é movido para 90°.
     - **0° (500 µs)**: O servo é movido para 0°.

### 3. **Movimento Suave do Servomotor e Efeito de Fade no LED**:
   - Após as etapas iniciais, o código entra em um loop contínuo, realizando um movimento suave do servomotor:
     - O servo move de 0° para 180° (aumento de pulse) e depois de 180° para 0° (diminuição de pulse), com um incremento de 5 µs em cada passo (definido por `SERVO_STEP`).
     - Durante o movimento do servo, o brilho do LED é ajustado para criar um efeito de "fade" (desvanecimento). O brilho do LED é incrementado ou decrementado com base na direção (`led_direction`). O LED alcança o brilho máximo (255) e começa a diminuir, ou atinge o brilho mínimo (0) e começa a aumentar.

### 4. **Controle do Brilho do LED**:
   - O brilho do LED é controlado pelo valor de `led_brightness`, que varia de 0 a 255.
   - A direção do efeito de fade é controlada pela variável `led_direction`, que alterna entre aumentar (1) e diminuir (-1) o brilho.
   - O PWM do LED é ajustado a cada incremento de movimento do servomotor, criando uma transição suave de brilho à medida que o servo se move.

### 5. **Atraso entre Incrementos**:
   - A cada incremento do movimento do servo e do brilho do LED, o código aguarda 10 ms (definido por `SERVO_DELAY_MS`) antes de continuar, garantindo um movimento suave do servo e uma transição gradual do brilho do LED.

### Como Funciona o Código:
1. O servomotor se move para a posição de 180° e permanece lá por 5 segundos, depois vai para 90° e, em seguida, para 0°.
2. Depois dessas etapas iniciais, o código entra em um loop contínuo onde o servomotor move-se suavemente de 0° para 180° e volta para 0°, enquanto o LED exibe um efeito de fade, alternando entre brilho crescente e decrescente.
3. O servo é controlado com precisão, realizando pequenos incrementos de 5 µs para um movimento suave, e o LED é ajustado para fornecer um efeito visual agradável.

Esse programa combina o controle de um servomotor com um LED RGB para criar um efeito visual e de movimento suave, útil em aplicações que exigem uma interação entre movimento físico e efeitos de luz.
