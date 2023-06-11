#define BUFF_SIZE 4000
#define RD_BLOCK_SIZE 128
char streamname[100];
char* IP_ADDRESS = "192.168.0.188";
char* PORT = "8899";
char req[36] = {165, 23, 0, 16, 69, 0, 0, 207, 45, 4, 142, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 3, 6, 4, 0, 5, 196, 128, 83, 21};
char req2[36] = {165, 23, 0, 16, 69, 0, 0, 207, 45, 4, 142, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 3, 5, 4, 0, 5, 196, 196, 150, 21};
char req3[36] = {165, 23, 0, 16, 69, 0, 0, 207, 45, 4, 142, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 3, 5, 196, 0, 3, 68, 250, 10, 21};
char req4[36] = {165, 23, 0, 16, 69, 0, 0, 207, 45, 4, 142, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 3, 4, 133, 0, 5, 149, 16, 51, 21};
char req5[36] = {165, 23, 0, 16, 69, 0, 0, 207, 45, 4, 142, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 3, 6, 132, 0, 24, 5, 97, 8, 21};
char req6[36] = {165, 23, 0, 16, 69, 0, 0, 207, 45, 4, 142, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 3, 4, 136, 0, 9, 4, 214, 111, 21};

sprintf(streamname, "/dev/tcp/%s/%s/", IP_ADDRESS, PORT); 
sleep(1000);

while(true)
{
	while(getinput(0)>0)
	{
     STREAM* pTcpStream = stream_create(streamname,0,0);   // create tcp stream
     printf("Stream start %s",IP_ADDRESS);
	 sleep(100);
     if (pTcpStream !=NULL) 
	 {
     	char* res;

     	stream_write(pTcpStream,req,36);
     	stream_flush(pTcpStream);

     	char szBuffer[BUFF_SIZE];
     	char szTmpBuffer[RD_BLOCK_SIZE];
     	int nCnt;
     	int nBytesReceived = 0;
     	int i = 0;

     	do
     	{
		 	nCnt = stream_read(pTcpStream,szTmpBuffer,RD_BLOCK_SIZE,4000);
		 	if(nCnt > 0)
				{
				printf("Received: %d %d %d %d %d %s",nCnt,szTmpBuffer[30],szTmpBuffer[31],szTmpBuffer[32],szTmpBuffer[33],IP_ADDRESS);
				setoutput(0,szTmpBuffer[37]); //battery capacity 37 low byte, 36 high byte

				float batteryV = (szTmpBuffer[28]*256+szTmpBuffer[29])*0.1;		//
				setoutput(1,batteryV);

				int batteryChargeINT  = szTmpBuffer[32]*256 +szTmpBuffer[33];
				if (batteryChargeINT > 32767) batteryChargeINT = batteryChargeINT - 65536;
				float batteryCharge = batteryChargeINT*0.01;	//0x020F
				setoutput(2,batteryCharge);

         		//strcpy((char*)szBuffer+nBytesReceived,szTmpBuffer,nCnt);
         		nBytesReceived += nCnt;
				}
     	} while (nCnt > 0);
     	szBuffer[nBytesReceived] = 0;


		// R E Q U E S T  2
     	stream_write(pTcpStream,req2,36);
     	stream_flush(pTcpStream);


     	do
     	{
		 	nCnt = stream_read(pTcpStream,szTmpBuffer,RD_BLOCK_SIZE,4000);
		 	if(nCnt > 0)
				{
				printf("Received: %d %d %d %d %d %s",nCnt,szTmpBuffer[28],szTmpBuffer[29],szTmpBuffer[32],szTmpBuffer[33],IP_ADDRESS);

				int activePowerINT  = szTmpBuffer[28]*256 +szTmpBuffer[29];
				if (activePowerINT > 32767) activePowerINT = activePowerINT - 65536;
				float activePower = activePowerINT*0.01;	//0x020F
				setoutput(3,activePower);

         		nBytesReceived += nCnt;
				}
     	} while (nCnt > 0);
     	szBuffer[nBytesReceived] = 0;

		// R E Q U E S T  3
     	stream_write(pTcpStream,req3,36);
     	stream_flush(pTcpStream);


     	do
     	{
		 	nCnt = stream_read(pTcpStream,szTmpBuffer,RD_BLOCK_SIZE,4000);
		 	if(nCnt > 0)
				{
				printf("Received: %d %d %d %d %d %s",nCnt,szTmpBuffer[28],szTmpBuffer[29],szTmpBuffer[32],szTmpBuffer[33],IP_ADDRESS);

				int PVPowerINT  = szTmpBuffer[28]*256 +szTmpBuffer[29];
				if (PVPowerINT > 32767) PVPowerINT = activePowerINT - 65536;
				float PVPower = PVPowerINT*0.1;	//0x020F
				setoutput(4,PVPower);

         		nBytesReceived += nCnt;
				}
     	} while (nCnt > 0);
     	szBuffer[nBytesReceived] = 0;


		// R E Q U E S T  4
     	stream_write(pTcpStream,req4,36);
     	stream_flush(pTcpStream);


     	do
     	{
		 	nCnt = stream_read(pTcpStream,szTmpBuffer,RD_BLOCK_SIZE,4000);
		 	if(nCnt > 0)
				{
				printf("Received: %d %d %d %d %d %s",nCnt,szTmpBuffer[28],szTmpBuffer[29],szTmpBuffer[32],szTmpBuffer[33],IP_ADDRESS);

				int GridPowerINT  = szTmpBuffer[28]*256 +szTmpBuffer[29];
				if (GridPowerINT > 32767) GridPowerINT = GridPowerINT - 65536;
				float GridPower = GridPowerINT*0.1;	//0x020F
				setoutput(5,GridPower);

         		nBytesReceived += nCnt;
				}
     	} while (nCnt > 0);
     	szBuffer[nBytesReceived] = 0;

		// R E Q U E S T  5
     	stream_write(pTcpStream,req5,36);
     	stream_flush(pTcpStream);

     	do
     	{
		 	nCnt = stream_read(pTcpStream,szTmpBuffer,RD_BLOCK_SIZE,4000);
		 	if(nCnt > 0)
				{
				printf("Received: %d %d %d %d %d %s",nCnt,szTmpBuffer[28],szTmpBuffer[29],szTmpBuffer[32],szTmpBuffer[33],IP_ADDRESS);

				int GenerationTodayINT  = szTmpBuffer[30]*256 +szTmpBuffer[31];
				float GenerationToday = GenerationTodayINT*0.01;	//		
				setoutput(6,GenerationToday);

				int ConsumptionTodayINT  = szTmpBuffer[38]*256 +szTmpBuffer[39];
				float ConsumptionToday = ConsumptionTodayINT*0.01;	//		
				setoutput(7,ConsumptionToday);

				int PurchaseTodayINT  = szTmpBuffer[46]*256 +szTmpBuffer[47];
				float PurchaseToday = PurchaseTodayINT*0.01;	//		
				setoutput(8,PurchaseToday);

				int SellingTodayINT  = szTmpBuffer[54]*256 +szTmpBuffer[55];
				float SellingToday = SellingTodayINT*0.01;	//		
				setoutput(9,SellingToday);


         		nBytesReceived += nCnt;
				}
     	} while (nCnt > 0);
     	szBuffer[nBytesReceived] = 0;

		// R E Q U E S T  6
     	stream_write(pTcpStream,req6,36);
     	stream_flush(pTcpStream);

     	do
     	{
		 	nCnt = stream_read(pTcpStream,szTmpBuffer,RD_BLOCK_SIZE,4000);
		 	if(nCnt > 0)
				{
				printf("Received: %d %d %d %d %d %s",nCnt,szTmpBuffer[28],szTmpBuffer[29],szTmpBuffer[32],szTmpBuffer[33],IP_ADDRESS);

				int ActivePowerINT  = szTmpBuffer[28]*256 +szTmpBuffer[29];
				if (ActivePowerINT > 32767) ActivePowerINT = ActivePowerINT - 65536;
				float ActivePower = ActivePowerINT*0.01;	//0x020F
				setoutput(10,ActivePower);


         		nBytesReceived += nCnt;
				}
     	} while (nCnt > 0);
     	szBuffer[nBytesReceived] = 0;


     	stream_close(pTcpStream);
     	printf("Stream Closed %s",IP_ADDRESS);
		sleep(5000);
	 }
    }
	sleep(1000);
}
