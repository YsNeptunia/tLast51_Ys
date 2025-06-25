#include "PW.h"
//���������غ���

void mPW_Shift(bit lr)//������������
{
	u8 i;
	if(lr == 0){//����
		for(i = pw_index;i < 8;i++){
			pw_input[i-1] = pw_input[i];
		}
		pw_input[7] = 0x40;
	}
	else{//����
		if(pw_index == 0){//��������
			for(i = 7;i > 0;i--){
				pw_input[i] = pw_input[i-1];
			}
			pw_input[0] = 0x40;
		}
		else{//����δ��
			for(i = 6;i >= pw_index;i--){
				pw_input[i+1] = pw_input[i];
			}
			pw_input[i+1] = 0x40;
		}
	}
}

void mPW_Ins(u8 b)//����һλ����
{
	if(pw_input[0] == 0x40){
		mPW_Shift(0);
		pw_index--;
		pw_input[7] = b;
	}
}

void mPW_Del(void)//ɾ��һλ����
{
	if(pw_input[7] != 0x40){
		mPW_Shift(1);
		pw_index++;
	}
}

void mPW_Clear(void){//������������
	u8 i;
	for(i = 0;i < 8;i++){
		pw_input[i] = 0x40;
	}
	pw_index = 8;
}

bit mPW_IsEmpty(void)//�ж����������Ƿ��пո�
{
    u8 i;
    for (i = 0; i < 8; i++) {
        if (pw_input[i] == 0x40) {
            return 1;
        }
    }
    return 0;
}

bit mPW_IsCorrect(void) // �����жϺ���
{
    u8 i, login;

    for (login = 0; login < USER_MAX; login++) {
        for (i = 0; i < 8; i++) {
            if (pw_input[i] != password[login][i]) {
                break; // �����ǰ���벻ƥ�䣬�����ڲ�ѭ��
            }
        }
        if (i == 8) { // ����ڲ�ѭ������������˵������ƥ��
            user = login;//��¼�û�IDȷ��
            return 1;
        }
    }
    return 0; // ����������붼��ƥ�䣬����0
}


//��������Ա�����жϺ���
bit mPW_IsAdmin(void)
{
	u8 i;
	for(i = 0;i < 8;i++){
		if(pw_input[i] != admin[i])
			return 0;
	}
	return 1;
}

void mPW_AdminSet(void)//���ù���Ա����
{
	u8 i;
	for(i = 0;i < 8;i++){
		admin[i] = pw_input[i];
	}
}

void mPW_Set(void)//��������
{
	u8 i;
	for(i = 0;i < 8;i++){
		password[user][i] = pw_input[i];
	}
}

void mPW_Read(void)//��E2PROM��ȡ���뵽����
{
	u8 i;
	for(i = 0;i < USER_MAX;i++)
		EEPROM_Read(password[i],i*8,8);
	EEPROM_Read(admin,i*8,8);
}

void mPW_Observe(void)//����Ա�ɶ�ȡ������
{
	u8 i;
	for(i = 0;i < 8;i++){
		pw_input[i] = password[user][i];
	}
}

void mPW_Main(void)//ɨ���������
{
    if ((pres == 0x18) || (pres == 0x14))
        mPW_Ins(0);
    if (pres == 0x28)
        mPW_Ins(1);
    if (pres == 0x24)
        mPW_Ins(2);
    if (pres == 0x22)
        mPW_Ins(3);
    if (pres == 0x48)
        mPW_Ins(4);
    if (pres == 0x44)
        mPW_Ins(5);
    if (pres == 0x42)
        mPW_Ins(6);
    if (pres == 0x88)
        mPW_Ins(7);
    if (pres == 0x84)
        mPW_Ins(8);
    if (pres == 0x82)
        mPW_Ins(9);
}
