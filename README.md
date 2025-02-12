# Controle de Servo Motor com Raspberry Pi Pico

## Descrição do Projeto

Este projeto utiliza uma **Raspberry Pi Pico** para controlar um **servo motor** através de **PWM (Pulse Width Modulation)**. O servo pode ser posicionado em **0°, 90° e 180°**, além de executar uma varredura suave entre esses ângulos.

## Componentes Utilizados

- **Raspberry Pi Pico**
- **Servo Motor (SG90 ou compatível)**
- **Jumpers para conexão**

## Funcionalidades

- Controle de um servo motor usando **PWM a 50Hz**.
- Posicionamento do servo em **0°, 90° e 180°**.
- **Varredura suave** de 0° a 180°.
- **Frequência e ciclo de trabalho ajustados** para compatibilidade com servos padrão.

## Configuração do Hardware

### **Pinos Utilizados:**

| Componente        | Pino na Pico |
| ----------------- | ------------ |
| Servo Motor (PWM) | GPIO 22      |

**Esquema de conexão:**

- **Fio Vermelho do Servo:** VCC (3.3V ou 5V da Pico)
- **Fio Preto/Marrom do Servo:** GND
- **Fio Amarelo/Branco do Servo:** GPIO 22

## Estrutura do Código

O projeto é dividido nas seguintes funções:

### 1. **`servo_pwm_init(gpio)`**

Inicializa o PWM no pino do servo, configurando:

- Frequência de 50Hz (Período de 20ms)
- Divisor de clock para ajustar os tempos de pulso
- Configuração inicial do PWM

### 2. **`servo_write_us(gpio, pulse_us)`**

Ajusta a largura de pulso do PWM, definindo o ângulo do servo.

### 3. **Loop principal (********`main()`********\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*)**

Executa:

1. **Movimentos fixos**: 0°, 90° e 180°.
2. **Varredura suave**: O servo se movimenta suavemente de 0° a 180° e volta.

## Como Compilar e Rodar

### **1. Instale o Raspberry Pi Pico SDK**

Siga as instruções oficiais do SDK:
[https://github.com/raspberrypi/pico-sdk](https://github.com/raspberrypi/pico-sdk)

### **2. Clone este repositório**

```sh
    git clone https://github.com/seu-usuario/seu-repositorio.git
    cd seu-repositorio
```

### **3. Abra o VS Code e importe o projeto:**

- Vá até a **Extensão Raspberry Pi Pico**.
- Selecione **Import Project**.
- Escolha a pasta do repositório clonado.
- Clique em **Import**.

### **4. Compile o código:**

- Utilize a opção de **Build** da extensão.

### **5. Carregue o binário na Pico**

1. Pressione e segure o **botão BOOTSEL** da Raspberry Pi Pico W.
2. Conecte-a ao PC via **USB**.
3. Copie o arquivo `.uf2` gerado para a unidade montada.

## Exemplo de Uso

1. O servo é inicializado e se move automaticamente para 180°.
2. Após 5 segundos, o servo se move para 90°.
3. Depois de mais 5 segundos, o servo vai para 0°.
4. O servo então realiza uma **varredura suave** de 0° a 180° e volta continuamente

##

## Autor

- [Gabriel Silva Sampaio]

- Video demonstração [https://www.dropbox.com/scl/fi/csfqedsyagpq4axpxkdq8/2025-02-11-23-48-55.mkv?rlkey=n890hmlnajgrf7wzzmij55167&st=k4zfdgk5&dl=0]

