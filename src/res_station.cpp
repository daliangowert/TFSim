#include "res_station.hpp"
#include "general.hpp"


res_station::res_station(sc_module_name name,int i, string n, map<string,int> inst_map, const nana::listbox::item_proxy item, const nana::listbox::cat_proxy c):
sc_module(name),
id(i),
type_name(n),
instruct_time(inst_map),
table_item(item),
cat(c)
{
	Busy = isFirst = false;
	vj = vk = qj = qk = a = 0;
	SC_THREAD(exec);
	sensitive << exec_event;
	dont_initialize();
	SC_METHOD(leitura);
	sensitive << in;
	dont_initialize();
}

void res_station::exec()
{
	while(true)
	{
		//Enquanto houver dependencia de valor em outra RS, espere
		while(qj || qk)
			wait(val_enc);
		cout << "Execuçao da instruçao " << op << " iniciada no ciclo " << sc_time_stamp() << " em " << name() << endl << flush;
		float res = 0;
		cat.at(instr_pos).text(EXEC,"X");
		if(op.substr(0,4) == "DADD")
			res = vj + vk;
		else if(op.substr(0,4) == "DSUB")
			res = vj - vk;
		else if(op.substr(0,4) == "DMUL")
			res = vj*vk;
		else if(op.substr(0,4) == "DDIV")
		{
			if(vk)
				res = vj/vk;
			else
				cout << "Divisao por 0, instrucao ignorada!" << endl;
		}
		else if(a)
		{
			a += vk;
			table_item->text(A,std::to_string(a));
			table_item->text(VK,"");
		}
		wait(sc_time(instruct_time[op],SC_NS));
		cat.at(instr_pos).text(WRITE,"X");
		if(!a)
		{
			string escrita_saida = std::to_string(id) + ' ' + std::to_string(res);
			cout << "Instrucao " << op << " completada no ciclo " << sc_time_stamp() << " em " << name() << " com resultado " << res << endl << flush;
			out->write(escrita_saida);
		}
		else
		{
			if(!isFirst)
				wait(isFirst_event);
			if(op.at(0) == 'L')
				mem_req(true,a,id);
			else
			{
				mem_req(false,a,vj);
				cout << "Instrucao " << op << " completada no ciclo " << sc_time_stamp() << " em " << name() << " gravando na posicao de memoria " << a << " o resultado " << vj << endl << flush;
			}
			isFirst = false;
			a = 0;
		}
		Busy = false;
		cout << "estacao " << id << " liberada no ciclo " << sc_time_stamp() << endl << flush;
		clean_item(); //Limpa a tabela na interface grafica
		wait();
	}
}

void res_station::leitura()
{
	if(qj || qk)
	{
		unsigned int i;
		int rs_source;
		string value;
		in->read(p);
		for(i = 0 ; i < p.size() && p[i] != ' '; i++)
			;
		rs_source = std::stoi(p.substr(0,i));
		if(qj == rs_source)
		{
			qj = 0;
			value = p.substr(i+1,p.size() - i - 1);
			vj = std::stoi(value);
			table_item->text(VJ,value);
			table_item->text(QJ,"");
			cout << "Instrucao " << op << " conseguiu o valor " << vj << " da RS_" << rs_source << endl << flush; 
			val_enc.notify(1,SC_NS);
		}
		if(qk == rs_source)
		{
			qk = 0;
			value = p.substr(i+1,p.size() - i - 1);
			vk = std::stoi(value);
			table_item->text(VK,value);
			table_item->text(QK,"");
			cout << "Instrucao " << op << " conseguiu o valor " << vk << " da RS_" << rs_source << endl << flush; 
			val_enc.notify(1,SC_NS);
		}
	}
}

void res_station::clean_item()
{
	for(unsigned i = 2 ; i < table_item->columns(); i++)
		table_item->text(i,"");
	table_item->text(BUSY,"False");
}

void res_station::mem_req(bool load,unsigned int addr,int value)
{
	string escrita_saida;
	string temp = std::to_string(addr) + ' ' + std::to_string(value);
	if(load)
		escrita_saida = "L " + temp;
	else
		escrita_saida = "S " + temp;
	out_mem->write(escrita_saida);
}