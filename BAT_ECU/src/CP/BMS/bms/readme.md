
生成代码中 set_bms_cmd.c 的函数要替换一下，后期改模型替换
CANSendMsg(1U, &bms_B.ux1801E410);



 //bms_cmd_send(&bms_B.ux1801E410);
  if((0!=GetXCPOTAStatus())&&(xQueue_forward_can_out2in!=NULL))
  	{
  		xQueueSend(xQueue_forward_can_out2in,&bms_B.ux1801E410,100/portTICK_PERIOD_MS);
  	}