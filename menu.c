#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "menu.h"
#include "zlg_cmd.h"
#include "serial.h"

unsigned char menu[] = "\r\n\
+********************** ZLG CMD HELP ************************+\r\n\
+--- Description ----+--CMD --+--- Demo ----+-- Remark------ +\r\n\
| read local cfg     | AT+1   | AT+1        |                |\r\n\
| search node        | AT+2   | AT+2        |                |\r\n\
| set channel nv     | AT+3   | AT+3 25     |                |\r\n\
| get remote info    | AT+4   | AT+4 0x2002 |                |\r\n\
| reset node         | AT+5   | AT+5 0x2002 |                |\r\n\
| restore factory settings    | AT+6 0x2002 |                |\r\n\
| set temp channel   | AT+7   | AT+7 25     |                |\r\n\
| set temp DstAddr   | AT+8   | AT+8 0x2002 |                |\r\n\
| set temp io dir    | AT+9   | AT+9 0x2002 0x55|            |\r\n\
| read temp io level | AT+A   | AT+A 0x2002 |                |\r\n\
| set temp io level  | AT+B   | AT+B 0x2002 0x55|            |\r\n\
| read temp adc value| AT+C   | AT+C 0x2002 |                |\r\n\
| set temp cast mode | AT+D   | AT+D 0x00   | broadcast:0x01 |\r\n\
| send to remote node| AT+S   | AT+S 0x2002 hello |          |\r\n\
| send               | send   | send hello  |                |\r\n\
| help               | ?      |             |                |\r\n\
+--------------------+--------+-------------+----------------+\r\n";

void send_data_test_thread(void)
{
	unsigned char wbuf[255];
	
	while(1)
	{
		if(fgets(wbuf,255,stdin))
		{
			unsigned short buffer;
			wbuf[strlen(wbuf)-1] = '\0';
			//printf("input wbuf is :%s,sizeof wbuf is:%d\r\n",wbuf,strlen(wbuf));
			//printf("atoi(wbuf[strlen(wbuf)-3]) %s is %d\r\n",wbuf,atoi(&wbuf[strlen(wbuf)-3]));
			//sscanf(&wbuf[strlen(wbuf)-4],"%04x",&buffer);
			//printf("buffer is 0x%04x\r\n",buffer);
			if(!strncmp(wbuf,"AT+1",4))
			{
				read_local_cfg();
			}
			else if(!strncmp(wbuf,"AT+2",4))
			{
				search_node();
			}
			else if(!strncmp(wbuf,"AT+3",4))
			{
				set_channel_nv(atoi(&wbuf[strlen(wbuf)-3]));
			}
			else if(!strncmp(wbuf,"AT+4",4))
			{
				unsigned short temp;
				unsigned char *string = NULL;
				string = &wbuf[strlen(wbuf)-6];
				if(!strncmp(string,"0x",2))
				{
					sscanf(&wbuf[strlen(wbuf)-4],"%04x",&temp);
					get_remote_info(temp);					
				}
				else
					printf("paramter error...\r\n");							
			}
			else if(!strncmp(wbuf,"AT+5",4))
			{
				unsigned short temp;
				unsigned char *string = NULL;
				string = &wbuf[strlen(wbuf)-6];
				if(!strncmp(string,"0x",2))
				{
					sscanf(&wbuf[strlen(wbuf)-4],"%04x",&temp);
					reset_node(temp);					
				}
				else
					printf("paramter error...\r\n");
				
			}
			else if(!strncmp(wbuf,"AT+6",4))
			{
				unsigned short temp;
				unsigned char *string = NULL;
				string = &wbuf[strlen(wbuf)-6];
				if(!strncmp(string,"0x",2))
				{
					sscanf(&wbuf[strlen(wbuf)-4],"%04x",&temp);
					restore_factory_settings(temp);					
				}
				else
					printf("paramter error...\r\n");
			}
			else if(!strncmp(wbuf,"AT+7",4))
			{
				set_temporary_channel(atoi(&wbuf[strlen(wbuf)-3]));
			}
			else if(!strncmp(wbuf,"AT+8",4))
			{
				unsigned short temp;
				if(!strncmp(&wbuf[strlen(wbuf)-6],"0x",2))
				{
					sscanf(&wbuf[strlen(wbuf)-4],"%04x",&temp);
					set_temporary_DestAddr(temp);					
				}
				else
					printf("paramter error...\r\n");
			}
			else if(!strncmp(wbuf,"AT+9",4))
			{
				unsigned short temp1;
				unsigned char temp2;
				if(!strncmp(&wbuf[strlen(wbuf)-11],"0x",2) && !strncmp(&wbuf[strlen(wbuf)-4],"0x",2))
				{
					sscanf(&wbuf[strlen(wbuf)-9],"%04x",&temp1);
					sscanf(&wbuf[strlen(wbuf)-2],"%02x",&temp2);
					set_temporary_io_dir(temp1,temp2);					
				}
				else
					printf("paramter error...\r\n");
			}
			else if(!strncmp(wbuf,"AT+A",4))
			{
				unsigned short temp;
				if(!strncmp(&wbuf[strlen(wbuf)-6],"0x",2))
				{
					sscanf(&wbuf[strlen(wbuf)-4],"%04x",&temp);
					read_temporary_io_level(temp);					
				}
				else
					printf("paramter error...\r\n");				
			}
			else if(!strncmp(wbuf,"AT+B",4))
			{
				unsigned short temp1;
				unsigned char temp2;
				if(!strncmp(&wbuf[strlen(wbuf)-11],"0x",2) && !strncmp(&wbuf[strlen(wbuf)-4],"0x",2))
				{
					sscanf(&wbuf[strlen(wbuf)-9],"%04x",&temp1);
					sscanf(&wbuf[strlen(wbuf)-2],"%02x",&temp2);
					set_temporary_io_level(temp1,temp2);					
				}
				else
					printf("paramter error...\r\n");				
			}
			else if(!strncmp(wbuf,"AT+C",4))
			{
				unsigned short temp;
				if(!strncmp(&wbuf[strlen(wbuf)-6],"0x",2))
				{
					sscanf(&wbuf[strlen(wbuf)-4],"%04x",&temp);
					read_temporary_adc_value(temp);					
				}
				else
					printf("paramter error...\r\n");				
			}
			else if(!strncmp(wbuf,"AT+D",4))
			{
				unsigned char temp;
				if(!strncmp(&wbuf[strlen(wbuf)-4],"0x",2))
				{
					sscanf(&wbuf[strlen(wbuf)-2],"%02x",&temp);
					set_temporary_cast_mode(temp);					
				}
				else
					printf("paramter error...\r\n");				
			}
			else if(!strncmp(wbuf,"AT+S",4))
			{
				unsigned short temp;
				if(!strncmp(&wbuf[5],"0x",2) && (strlen(wbuf) > 12))
				{
					sscanf(&wbuf[7],"%04x",&temp);
					send_data_to_remote_node(temp,&wbuf[12],strlen(wbuf)-12);					
				}
				else
					printf("paramter error...\r\n");
			}
			
			else if(!strncmp(wbuf,"help",4) || !strncmp(wbuf,"?",1))
				printf(menu);
			else if(wbuf[0] == '\0')
			{
				//printf("zlg_zm516x > ");
				//continue;
			}
		    else if(!strncmp(wbuf,"send",4))
			{
				WriteComPort(&wbuf[5],strlen(wbuf)-5);
			}
			else
				printf("command not found!press \"?\" to check command\r\n");
			memset(wbuf,0x0,strlen(wbuf) + 1);
			printf("zlg_zm516x > ");
		}
	}
}