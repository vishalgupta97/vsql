#include "metadata.h"
Root::Root()
{
	type=0;
	pugi::xml_parse_result result=doc.load_file("db.xml");
	node=doc.child("databases");
	type=0;
	for(auto i=node.begin();i!=node.end();i++)
	{
		Database *db=new Database(*i);
		databases.insert({string(i->name()),db});
	}
}
void Root::save()
{
	doc.save_file("db.xml");
}
Database::Database(pugi::xml_node &node1)
{
	type=1;
	node=node1;
	name=node.name();
	book=xlCreateBook();
	string s=name;
	book->load(s.append(".xls").c_str());
	cnt=node.attribute("count").as_int();
	for(auto i=node.begin();i!=node.end();i++)
	{
		Table *tbl=new Table(*i,book);
		tables.insert({string(i->name()),tbl});
	}	
}
void Database::save()
{
	string s=name;
	for(auto i=tables.begin();i!=tables.end();i++)
		i->second->save();
	book->save(s.append(".xls").c_str());
}
Table::Table(pugi::xml_node &node1,libxl::Book* book)
{
	type=2;
	node=node1;
	name=node.name();
	idx=node.attribute("index").as_int();
	rowcnt=node.attribute("rowcnt").as_int();
	pkcnt=node.attribute("pkcnt").as_int();
	col_cnt=node.attribute("count").as_int();
	sheet=book->getSheet(idx);
	pugi::xml_node clmns=node.child("columns");
	for(auto i=clmns.begin();i!=clmns.end();i++)
	{
		Column *clmn=new Column(*i);
		columns.insert({string(i->name()),clmn});
	}
	pugi::xml_node unique=node.child("unique");
	for(auto i=unique.begin();i!=unique.end();i++)
	{
		keys[i->name()];
	}
	pugi::xml_node foreign=node.child("foreign");
	for(auto i=foreign.begin();i!=foreign.end();i++)
	{
		foreign_keys.insert({i->name(),{i->attribute("to_tbl").value(),i->attribute("to_clmn").value()}});
	}
	primary_name=node.child("primary").first_child().name();
	pugi::xml_node rows_node=node.child("rows");
	for(auto i=rows_node.begin();i!=rows_node.end();i++)
	{
		rows.insert({i->attribute("i").as_int(),i->attribute("l").as_int()});
	}
	Column* primary_clmn=columns[primary_name];
	for(auto i=rows.begin();i!=rows.end();i++)
	{
		int idx=i->first,length=i->second;
		for(int j=idx;j<idx+length;j++)
		{
			switch(primary_clmn->datatype)
			{
				case 1:primary.insert(to_string((int)sheet->readNum(j,primary_clmn->idx)));
				break;
				case 2:primary.insert(to_string(sheet->readNum(j,primary_clmn->idx)));
				break;
				case 3:
				case 4:primary.insert(string(sheet->readStr(j,primary_clmn->idx)));
				break;
			}
		}
	}
}
void Table::save()
{
	if(rows_change)
	{
		node.remove_child("rows");
		pugi::xml_node rows_node=node.append_child("rows");
		for(auto i=rows.begin();i!=rows.end();i++)
		{
			pugi::xml_node n=rows_node.append_child("n");
			n.append_attribute("i").set_value(i->first);
			n.append_attribute("l").set_value(i->second);
		}
	}
}
Column::Column(pugi::xml_node &node1)
{
	type=3;
	node=node1;
	name=node.name();
	for(int i=0;i<5;i++)
		attr[i]=false;
	for(auto i=node.attributes_begin();i!=node.attributes_end();i++)
	{
		if(strcmp("datatype",i->name())==0)
			datatype=i->as_int();
		else if(strcmp("index",i->name())==0)
			idx=i->as_int();
		else if(strcmp("unique",i->name())==0)
			attr[0]=true;
		else if(strcmp("primary",i->name())==0)
			attr[1]=true;
		else if(strcmp("auto_inc",i->name())==0)
			attr[2]=true;
		else if(strcmp("not_null",i->name())==0)
			attr[3]=true;
		else attr[4]=true;
	}
}