# uc-projeto-final
Projeto Final de Microcontroladores - UTFPR

# Pinos Utilizados

## I²C
* **PB2** : ```I2C0SCL```
* **PB3** : ```I2C0SDA```


# I²C
* Possible Slave Addresses:

  * ```0111100```
  * ```0111101```

* Write Mode

  * ```0```


# Modelo de Dados de Teste
```N"74",P"IIOIIOGOIIOIIV","T111111G111111V

pinagem[14]

teste[14]

i = 3;

for;;
if(pinagem[i] == "I")
  set_output(1)

for;;
if(pinagem[i] == "O")
  test_result = read_pin(i) & teste

    if(test_result == 0) {
      error_pin = i;
      return 0;
    };
  

return 1;

```



  