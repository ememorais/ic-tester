#include "test.h"
#include "memory.h"

int32_t Verify_mem(char *code_ic){
		int i;
		const char *mem_pointer = memory;
		for(i=0;i<strlen(memory);i++){
			if(*(mem_pointer+i)=='N'){
				int j;
				char code_ic_temp[7];
				for(j=0;*(mem_pointer+i+j+1)!='_';j++){
					code_ic_temp[j]=*(mem_pointer+i+j+1);
				}
				if(strcmp(code_ic_temp,code_ic)==0){
					return i;
				}
			}
		}
		return -1;
}

uint32_t GPIO_config(int pos){
		int i = pos;
		const char *mem_pointer = memory;
		do{
		i++;
		}while(*(mem_pointer+i)!='P');
		int j;
		for(j=1;*(mem_pointer+j+i)!='_';j++){
			if(*(mem_pointer+j+i)=='0'){
				Set_Input(j);
			}
			else{
				Set_Output(j);
			}
		}
		return Exec_teste(i+j+1);
}

uint32_t Char_toHex(int pos){
	int j, pino = 0, resultado = 0;
	const char *mem_pointer = memory;
	for(j=0;j<19;j++){
		pino = *(mem_pointer+pos+j) == '1'? 1:0;
		resultado |= (pino<<(18-j));
	}
	return resultado; 
}

uint32_t Exec_teste(int pos){
		int i,teste,port_data;
		const char *mem_pointer = memory;
		for(i=pos+1;*(mem_pointer+i-1)!='N';i=i+21){
			teste = Char_toHex(i);
			PortE_Output(0x3F & teste);
			PortK_Output(0x7F & teste>>6);
			PortN_Output(teste>>13);
			SysTick_Wait1ms(100);
			port_data = PortE_Input()|(PortK_Input()<<6)|(PortN_Input()<<13);
			if(port_data!=teste){
				return (port_data^teste);
			}	
		}
		return 1;
}
