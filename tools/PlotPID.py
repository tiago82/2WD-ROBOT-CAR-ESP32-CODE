import serial
import re
import matplotlib.pyplot as plt

# Inicializa a comunicação serial com o Arduino
arduino_port = 'COM6'  # Altere para a porta serial correta
baud_rate = 9600  # Ajuste para a mesma taxa configurada no Arduino
ser = serial.Serial(arduino_port, baud_rate)

# Prepara o gráfico
plt.ion()  # Ativa o modo de atualização interativa
fig, ax = plt.subplots()
ax.set_xlabel('Tempo')
ax.set_ylabel('Valor')

# Variáveis para armazenar os dados
tempo = []
setpoints = []
entradas = []
saidas = []

# Cria as linhas do gráfico uma vez
setpoint_line, = ax.plot(tempo, setpoints, label='Setpoint')
entrada_line, = ax.plot(tempo, entradas, label='Entrada')
saida_line, = ax.plot(tempo, saidas, label='Saída')
ax.legend()  # Adiciona legenda ao gráfico

try:
    while True:
        # Lê os dados da porta serial
        line = ser.readline().decode('utf-8').rstrip()
        if line:
            # Utiliza expressões regulares para extrair os valores de setpoint, entrada e saída
            setpoint_match = re.search(r'setpoint: (\d+\.\d+)', line)
            input_match = re.search(r'input: (\d+\.\d+)', line)
            output_match = re.search(r'output: (\d+\.\d+)', line)
            
            if setpoint_match and input_match and output_match:
                setpoint = float(setpoint_match.group(1))
                entrada = float(input_match.group(1))
                saida = float(output_match.group(1))

                tempo.append(len(tempo))  # Tempo fictício (pode ser substituído por um timer real)
                setpoints.append(setpoint)
                entradas.append(entrada)
                saidas.append(saida)

                # Atualiza os dados nas linhas do gráfico
                setpoint_line.set_xdata(tempo)
                setpoint_line.set_ydata(setpoints)
                entrada_line.set_xdata(tempo)
                entrada_line.set_ydata(entradas)
                saida_line.set_xdata(tempo)
                saida_line.set_ydata(saidas)

                # Redesenha o gráfico
                ax.relim()
                ax.autoscale_view()
                plt.pause(0.05)  # Intervalo de atualização do gráfico

except KeyboardInterrupt:
    # Encerra a comunicação serial e fecha o gráfico ao pressionar Ctrl+C
    ser.close()
    plt.ioff()
    plt.show()
