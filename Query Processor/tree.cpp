#include "tree.h"
void Cond_exp::check(Table* tbl)
{
	auto it=tbl->columns.find(*lhs);
	if(it==tbl->columns.end())
	{
		error=true;
		printf("Column does not exist\n");
		return;
	}
	if(it->second->datatype!=rhs->type)
	{
			error=true;
			printf("Datatype mismatch\n");
			return;
	}
	if((op_type!=1&&op_type!=6)&&(rhs->type==3||rhs->type==4))
	{
		error=true;
		printf("that one\n");
		return;
	}
	col_idx=it->second->idx;
}
std::string Cond_exp::gen(int &cnt,Where_stmt* stmt)
{
	stmt->exps.push_back(this);
	string s="t"+to_string(cnt);
	cnt++;
	return s;
}
void And_exp::check(Table* tbl)
{
	lhs->check(tbl);
	if(lhs->error)
		error=true;
	else
	{
		rhs->check(tbl);
		if(rhs->error)
			error=true;
	}
}
std::string And_exp::gen(int &cnt,Where_stmt* stmt)
{
	string s=" ";
	if(lhs->type==1)
	{
		s+="t"+to_string(cnt);
		cnt++;
		stmt->exps.push_back(static_cast<Cond_exp*>(lhs));
	}
	else
		s+=lhs->gen(cnt,stmt);
	s+=" & ";
	if(rhs->type==1)
	{
		s+="t"+to_string(cnt);
		cnt++;
		stmt->exps.push_back(static_cast<Cond_exp*>(rhs));
	}
	else
		s+=rhs->gen(cnt,stmt);
	return s;
}
void Or_exp::check(Table* tbl)
{
	lhs->check(tbl);
	if(lhs->error)
		error=true;
	else
	{
		rhs->check(tbl);
		if(rhs->error)
			error=true;
	}
}
std::string Or_exp::gen(int &cnt,Where_stmt* stmt)
{
	string s=" ";
	if(lhs->type==1)
	{
		s+="t"+to_string(cnt);
		cnt++;
		stmt->exps.push_back(static_cast<Cond_exp*>(lhs));
	}
	else
		s+=lhs->gen(cnt,stmt);
	s+=" | ";
	if(rhs->type==1)
	{
		s+="t"+to_string(cnt);
		cnt++;
		stmt->exps.push_back(static_cast<Cond_exp*>(rhs));
	}
	else
		s+=rhs->gen(cnt,stmt);
	return s;
}
bool Where_stmt::check(Table* tbl)
{
	exp->check(tbl);
	return exp->error;
}
void Where_stmt::execute(Table* tbl,int limit)
{
	int cnt=0,rowno=tbl->rowcnt;
	std::string s=exp->gen(cnt,this);
	LibBoolEE::Vals vals;
	for(int i=0;i<cnt;i++)
		vals.insert({"t"+to_string(i),false});
	bool temp=false;
	for(int i=1;i<=rowno;i++)
	{
		for(int j=0;j<cnt;j++)
		{
			switch(exps[j]->op_type)
			{
				case 1:switch(exps[j]->rhs->type)
				{
					case 1:temp=tbl->sheet->readNum(i,exps[j]->col_idx)==exps[j]->rhs->x.int_val;
					break;
					case 2:temp=tbl->sheet->readNum(i,exps[j]->col_idx)==exps[j]->rhs->x.dbl_val;
					break;
					case 3:
					case 4:temp=exps[j]->rhs->x.s->compare(tbl->sheet->readStr(i,exps[j]->col_idx))==0;
					break;
				}
				break;
				case 2:switch(exps[j]->rhs->type)
				{
					case 1:temp=tbl->sheet->readNum(i,exps[j]->col_idx)<exps[j]->rhs->x.int_val;
					break;
					case 2:temp=tbl->sheet->readNum(i,exps[j]->col_idx)<exps[j]->rhs->x.dbl_val;
					break;
				}
				break;
				case 3:switch(exps[j]->rhs->type)
				{
					case 1:temp=tbl->sheet->readNum(i,exps[j]->col_idx)>exps[j]->rhs->x.int_val;
					break;
					case 2:temp=tbl->sheet->readNum(i,exps[j]->col_idx)>exps[j]->rhs->x.dbl_val;
					break;
				}
				break;
				case 4:switch(exps[j]->rhs->type)
				{
					case 1:temp=tbl->sheet->readNum(i,exps[j]->col_idx)<=exps[j]->rhs->x.int_val;
					break;
					case 2:temp=tbl->sheet->readNum(i,exps[j]->col_idx)<=exps[j]->rhs->x.dbl_val;
					break;
				}
				break;
				case 5:switch(exps[j]->rhs->type)
				{
					case 1:temp=tbl->sheet->readNum(i,exps[j]->col_idx)>=exps[j]->rhs->x.int_val;
					break;
					case 2:temp=tbl->sheet->readNum(i,exps[j]->col_idx)>=exps[j]->rhs->x.dbl_val;
					break;
				}
				break;
				case 6:switch(exps[j]->rhs->type)
				{
					case 1:temp=tbl->sheet->readNum(i,exps[j]->col_idx)!=exps[j]->rhs->x.int_val;
					break;
					case 2:temp=tbl->sheet->readNum(i,exps[j]->col_idx)!=exps[j]->rhs->x.dbl_val;
					break;
					case 3:
					case 4:temp=exps[j]->rhs->x.s->compare(tbl->sheet->readStr(i,exps[j]->col_idx))!=0;
					break;
				}
				break;
			}
			vals["t"+to_string(j)]=temp;
		}
		if(LibBoolEE::resolve(s,vals))
		{
			res.push_back(i);
			if(limit>0&&res.size()==limit)
				break;
		}
	}
}
bool Orderby_stmt::check(Table* tbl)
{
	for(int i=0;i<clmns_list->size();i++)
	{
		auto it=tbl->columns.find(clmns_list->at(i)->first->c_str());
		if(it!=tbl->columns.end())
			index_type.push_back({it->second->idx,it->second->datatype});
		else
			return true;
	}
	return false;
}
void Orderby_stmt::execute(Table* tbl)
{
	this->sheet=tbl->sheet;
	sort(res.begin(),res.end(),[this](int i, int j){
		double val,val1;
		int diff;
		for(int k=0;k<this->index_type.size();k++)
		{
			switch(this->index_type[k].second)
			{
				case 1:
				case 2:val=this->sheet->readNum(i,this->index_type[k].first);
				val1=this->sheet->readNum(j,this->index_type[k].first);
				if(val>val1)
					return !(this->clmns_list->at(k)->second);
				else if(val1<val)
					return this->clmns_list->at(k)->second;
				break;
				case 3:
				case 4:
				string s=string(this->sheet->readStr(i,this->index_type[k].first));
				diff=s.compare(this->sheet->readStr(j,this->index_type[k].first));
				if(diff>0)
					return !(this->clmns_list->at(k)->second);
				else if(diff<0)
					return this->clmns_list->at(k)->second;
				printf("%d\n",diff);
				break;
			}
		}
		return false;
	});
}
void Update_stmt::check(Data *d)
{
	Database* db=static_cast<Database*>(d);
	auto it=db->tables.find(*tbl_name);
	if(it==db->tables.end())
	{
		error=true;
		error_msg="Table does not exist";
		return;
	}
	Table* tbl=it->second;
	for(int i=0;i<list->size();i++)
	{
		auto j=tbl->columns.find(*(list->at(i)->first));
		if(j==tbl->columns.end())
		{
			error=true;
			error_msg="Column name does not exist";
			return;
		}
		if(j->second->datatype!=list->at(i)->second->type)
		{
			error=true;
			error_msg="Type mismatch";
			return;
		}
		if(j->second->attr[0])
			unique_col_update=true;
		index_type.push_back({j->second->idx,j->second->datatype});
	}
	if(where_cond&&where_cond->check(tbl))
	{
		error=true;
		error_msg="Error in Where clause";
		return;
	}
	if(orderby_cond&&orderby_cond->check(tbl))
	{
		error=true;
		error_msg="Error in Orderby clause";
		return;
	}
	for(auto i=tbl->rows.begin();i!=tbl->rows.end();i++)
	{
		int idx=i->first,length=i->second;
		for(int j=idx;j<idx+length;j++)
			res.push_back(j);
	}
	if(where_cond)
	{
		where_cond->execute(tbl,limit);
		if(orderby_cond)
		{
			orderby_cond->res=where_cond->res;
			orderby_cond->execute(tbl);
			res=orderby_cond->res;
		}
		else
			res=where_cond->res;
	}
	else if(orderby_cond)
	{
		orderby_cond->res=res;
		orderby_cond->execute(tbl);
		res=orderby_cond->res;
	}
	if(unique_col_update&&res.size()>1)
	{
		error=true;
		error_msg="Same unique key after updation";
		return;
	}
}
void Update_stmt::execute(Data *d)
{
	Database *db=static_cast<Database*>(d);
	auto it=db->tables.find(*tbl_name);
	Table* tbl=it->second; 
	for(int i=0;i<res.size();i++)
	{
		for(int j=0;j<index_type.size();j++)
		{
			switch(index_type[j].second)
			{
				case 1:
				tbl->sheet->writeNum(res[i],index_type[j].first,list->at(j)->second->x.int_val);
				break;
				case 2:
				tbl->sheet->writeNum(res[i],index_type[j].first,list->at(j)->second->x.dbl_val);
				break;
				case 3:
				case 4:
				tbl->sheet->writeStr(res[i],index_type[j].first,list->at(j)->second->x.s->c_str());
				break;
			}
		}
	}
}
void Select_stmt::check(Data *d)
{
	Database *db=static_cast<Database*>(d);
	auto it=db->tables.find(*tbl_name);
	if(it==db->tables.end())
	{
		error=true;
		error_msg="Table does not exist";
		return;
	}
	Table* tbl=it->second;
	if(col_list)
	{
		for(int i=0;i<col_list->size();i++)
		{
			auto clmn=tbl->columns.find(*(col_list->at(i)));
			if(clmn==tbl->columns.end())
			{
				error=true;
				error_msg="Column name does not exist";
				return;
			}
			else
			{
				index_type.push_back({clmn->second->idx,clmn->second->datatype});
			}
		}
	}
	if(where_cond&&where_cond->check(tbl))
	{
		error=true;
		error_msg="Error in Where clause";
		return;
	}
	if(orderby_cond&&orderby_cond->check(tbl))
	{
		error=true;
		error_msg="Error in Orderby clause";
		return;
	}
}
void Select_stmt::execute(Data *d)
{
	Database *db=static_cast<Database*>(d);
	auto it=db->tables.find(*tbl_name);
	Table* tbl=it->second;
	int rowcnt=tbl->rowcnt;
	libxl::Sheet* sheet=tbl->sheet;
	vector<int> res;
	for(auto i=tbl->rows.begin();i!=tbl->rows.end();i++)
	{
		int idx=i->first,length=i->second;
		for(int j=idx;j<idx+length;j++)
			res.push_back(j);
	}
	if(where_cond)
	{
		where_cond->execute(tbl,limit);
		if(orderby_cond)
		{
			orderby_cond->res=where_cond->res;
			orderby_cond->execute(tbl);
			res=orderby_cond->res;
		}
		else
			res=where_cond->res;
	}
	else if(orderby_cond)
	{
		orderby_cond->res=res;
		orderby_cond->execute(tbl);
		res=orderby_cond->res;
	}
	int cols_count=tbl->col_cnt;
	if(!col_list)
	{
		pugi::xml_node clmns=tbl->node.child("columns");
		for(auto i=clmns.begin();i!=clmns.end();i++)
		{
			Column* clmn=tbl->columns[i->name()];
			index_type.push_back({clmn->idx,clmn->datatype});
		}
	}
	if(limit>0&&res.size()>limit)
		res.resize(limit);
	for(int i=0;i<res.size();i++)
	{
		for(int j=0;j<index_type.size();j++)
			switch(index_type[j].second)
			{
				case 1: printf("%d ",(int)sheet->readNum(res[i],index_type[j].first));break;
				case 2: printf("%lf ",sheet->readNum(res[i],index_type[j].first));
				break;
				case 3:
				case 4: printf("%s ",sheet->readStr(res[i],index_type[j].first));
				break;
			}
		printf("\n");
	}
}
void Db_drop::check(Data *d)
{
	Root *root=static_cast<Root*>(d);
	auto it=root->databases.find(*db_name);
	if(it==root->databases.end())
	{
		error=true;
		error_msg="Database does not exist";
		return;
	}
	if(curdb==it->second)
	{
		error=true;
		error_msg="Cannot drop current db";
		return;
	}
}
void Db_drop::execute(Data *d)
{
	Root *root=static_cast<Root*>(d);
	auto it=root->databases.find(*db_name);
	string s=it->first;
	remove(s.append(".xls").c_str());
	root->node.remove_child(it->second->node);
	root->databases.erase(it);
}
void Tbl_drop::check(Data *d)
{
	Database *db=static_cast<Database*>(d);
	for(int i=0;i<tbl_list->size();i++)
		if(db->tables.find(*(tbl_list->at(i)))==db->tables.end())
		{
			error=true;
			error_msg="Table name does not exist";
			return;
		}
}
void Tbl_drop::execute(Data *d)
{
	Database *db=static_cast<Database*>(d);
	for(int i=0;i<tbl_list->size();i++)
	{
		auto it=db->tables.find(*(tbl_list->at(i)));
		db->book->delSheet(it->second->idx);
		db->node.remove_child(it->second->node);
		db->tables.erase(it);
		db->cnt--;
	}
	db->node.attribute("count").set_value(db->cnt);
}
void Idx_drop::check(Data *d)
{
	
}
void Idx_drop::execute(Data *d)
{
	
}
void View_drop::check(Data *d)
{
	
}
void View_drop::execute(Data *d)
{
	
}
void Db_create::check(Data *d)
{
	Root *root=static_cast<Root*>(d);
	auto it=root->databases.find(*db_name);
	if(it!=root->databases.end())
	{
		error=true;
		error_msg="Database already exist";
	}
}
void Db_create::execute(Data *d)
{
	Root *root=static_cast<Root*>(d);
	Database *db=new Database();
	db->name=*db_name;
	db->book=xlCreateBook();
	db->node=root->node.append_child(db_name->c_str());
	db->book->addSheet(string("Sheet1").c_str());
	string s=db->name;
	db->book->save(s.append(".xls").c_str());
	db->node.append_attribute("count").set_value(0);
	root->databases.insert({*db_name,db});
}
void Tbl_create::check(Data *d)
{
	if(!tbl_name)
	{
		error=true;
		error_msg="Table name not provided";
		return;
	}
	if(!list)
	{
		error=true;
		error_msg="Table defination not provided";
		return;
	}
	Database *db=static_cast<Database*>(d);
	if(db->tables.find(*tbl_name)!=db->tables.end())
	{
		error=true;
		error_msg="Table already exist";
		return;
	}
	bfl=new bloom_filter();
	bool primary_key=false;
	string *auto_inc=NULL;
	std::stable_sort(list->begin(),list->end(),[](Create_def* a,Create_def* b){
		return a->type<b->type;
	});
	for(int i=0;i<list->size();i++)
	{
		if(list->at(i)->type==1)
		{
			Col_def *cd=list->at(i)->x.cd;
			if(bfl->chk_hash(cd->col_name->c_str()))
			{
				string s=*(cd->col_name);
				for(int j=0;j<i;j++)
				{
					if(list->at(j)->type==1&&list->at(j)->x.cd->col_name->compare(s)==0)
					{
						error=true;
						error_msg="Columns with same name";
						return;
					}
				}
			}
			if(cd->list)
			{
				for(int i=0;i<cd->list->size();i++)
					switch(cd->list->at(i)->type)
					{
						case 2:if(auto_inc==NULL)auto_inc=cd->col_name;
						else 
						{
							error=true;
							error_msg="Two Auto Increment found";
							return;
						}
						break;
						case 3:if(primary_key)
								{
									error=true;
									error_msg="Primary Key already defined";
									return;
								}
								else
								primary_key=true;
							break;
						case 5:
						auto it=db->tables.find(*(cd->list->at(i)->tbl_name));
						if(it==db->tables.end())
						{
							error=true;
							error_msg="Foreign key table not found";
						}
						auto it1=it->second->columns.find(*(cd->list->at(i)->col_name));
						if(it1==it->second->columns.end())
						{
							error=true;
							error_msg="Foreign key column not found";
						}
						if(!(it1->second->attr[0]))
						{
							error=true;
							error_msg="Foreign Key Column in not unique";
							return;
						}
						break;
					}
			}
		} 
		else
		{
			Constraints *con=list->at(i)->x.con;
			if(con->type==1)
			{
				if(auto_inc!=NULL)
				{
					if(primary_key)
					{
						error=true;
						error_msg="Primary Key already defined";
						return;
					}
				}
				else if(con->col_list->size()!=1||con->col_list->at(0)->compare(*auto_inc)!=0)
				{
					error=true;
					error_msg="Primary Key already defined";
					return;
				}
			}
			for(int j=0;j<con->col_list->size();j++)
			{
				if(!bfl->chk_hash(con->col_list->at(j)->c_str()))
				{
					error=true;
					error_msg="Column does not exist";
					return;
				}
			}
			if(con->type==4)
			{
				if(con->col_list->size()!=con->to_list->size())
				{
					error=true;
					error_msg="Foreign Key list does not match Primary Key list";
					return;
				}
				auto it=db->tables.find(*(con->tbl_name_to));
				if(it==db->tables.end())
				{
					error=true;
					error_msg="Foreign Table does not exist";
					return;
				}
				Table *to_tbl=it->second;
				string s="";
				for(int j=0;j<con->to_list->size();j++)
				{
					if(!bfl->chk_hash(con->col_list->at(j)->c_str())||to_tbl->columns.find(*(con->to_list->at(j)))==to_tbl->columns.end())
					{
						error=true;
						error_msg="Column does not exist";
						return;
					}
					else
					{
						s+=*(con->to_list->at(j))+"-";
					}
				}
				if(con->to_list->size()==1)
					s=s.substr(0,s.length()-1);
				if(to_tbl->keys.find(s)==to_tbl->keys.end())
				{
					error=true;
					error_msg="Foreign Key Columns are not unique";
					return;
				}
			}
		}
	}	
}
void Tbl_create::execute(Data *d)
{
	Database *db=static_cast<Database*>(d);
	Table *tbl=new Table();
	db->tables.insert({*tbl_name,tbl});
	printf("here2\n");
	tbl->name=*tbl_name;
	tbl->node=db->node.append_child(tbl_name->c_str());
	db->cnt++;
	db->node.attribute("count").set_value(db->cnt);
	printf("here3\n");
	tbl->node.append_attribute("index").set_value(db->cnt);
	tbl->idx=db->cnt;
	tbl->node.append_attribute("rowcnt").set_value("0");
	tbl->sheet=db->book->addSheet(tbl_name->c_str());
	printf("here4\n");
	pugi::xml_node clmns=tbl->node.append_child("columns");
	pugi::xml_node unique_key=tbl->node.append_child("unique");
	pugi::xml_node foreign_key=tbl->node.append_child("foreign");
	pugi::xml_node primary_key=tbl->node.append_child("primary");
	tbl->node.append_child("rows");
	int col_cnt=0;
	for(int i=0;i<list->size();i++)
	{
		if(list->at(i)->type==1)
		{
			col_cnt++;
			Col_def* cd=list->at(i)->x.cd;
			Column *clmn=new Column();
			clmn->name=*(cd->col_name);
			tbl->columns.insert({clmn->name,clmn});
			clmn->node=clmns.append_child(cd->col_name->c_str());
			clmn->node.append_attribute("datatype").set_value(datatype_vals[*(cd->datatype)]);
			clmn->datatype=datatype_vals[*(cd->datatype)];
			clmn->node.append_attribute("index").set_value(i+1);
			clmn->idx=i+1;
			bool not_null=false,ainc=false,primary=false,unique=false,foreign=false;
			Special_ele *se=NULL;
			if(cd->list)
			{
				for(int j=0;j<cd->list->size();j++)
				{
					switch(cd->list->at(j)->type)
					{
						case 1:not_null=true;
						break;
						case 2:ainc=true;break;
						case 3:primary=true;not_null=true;unique=true;break;
						case 4:unique=true;break;
						case 5:foreign=true;se=cd->list->at(j);break;
					}
				}
			}
			if(unique)
			{
				clmn->node.append_attribute("unique");
				clmn->attr[0]=true;
				tbl->keys[clmn->name];
				if(!primary)
					unique_key.append_child(clmn->name.c_str());
			}
			if(primary)
			{
				clmn->node.append_attribute("primary");
				clmn->attr[1]=true;
				tbl->primary_name=clmn->name;
				primary_key.append_child(clmn->name.c_str());
			}
			if(ainc)
			{
				clmn->node.append_attribute("auto_inc");
				clmn->attr[2]=true;
				tbl->node.append_attribute("pkcnt").set_value(0);//primary key counter
			}
			if(not_null)
			{
				clmn->node.append_attribute("not_null");
				clmn->attr[3]=true;
			}
			if(foreign)
			{
				clmn->node.append_attribute("foreign");
				clmn->attr[4]=true;
				pugi::xml_node foreign_node=foreign_key.append_child(clmn->name.c_str());
				foreign_node.append_attribute("to_tbl").set_value(se->tbl_name->c_str());
				foreign_node.append_attribute("to_clmn").set_value(se->col_name->c_str());
				tbl->foreign_keys.insert({clmn->name,{*(se->tbl_name),*(se->col_name)}});
			}	
		}
		else
		{
			Constraints *con=list->at(i)->x.con;
			if(con->col_list->size()>1)
			{
				string s="";
				for(int j=0;j<con->col_list->size();j++)
				{
					s+=*(con->col_list->at(j))+"-";
				}
				switch(con->type)
				{
					case 1:
					primary_key.append_child(s.c_str());
					tbl->primary_name=s;
					break;
					case 2:unique_key.append_child(s.c_str());
					tbl->keys[s];
					break;
					case 3:unique_key.append_child(s.c_str());
					tbl->keys[s];
					break;
					case 4:
					pugi::xml_node foreign_node=foreign_key.append_child (s.c_str());
					foreign_node.append_attribute("foreign_tbl").set_value(con->tbl_name_to->c_str());
					string y="";
					for(int j=0;j<con->to_list->size();j++)
						y+=*(con->to_list->at(j))+"-";
					foreign_node.append_attribute("foreign_clmn").set_value(y.c_str());
					tbl->foreign_keys[s]={*(con->tbl_name_to),y};
					break;
				}
			}
			else
			{
				Column *clmn=(tbl->columns.find(*(con->col_list->at(0)))->second);
				switch(con->type)
				{
					case 1:
					clmn->node.append_attribute("unique");
					clmn->node.append_attribute("primary");
					clmn->node.append_attribute("not_null");
					clmn->attr[0]=true;
					clmn->attr[1]=true;
					clmn->attr[3]=true;
					primary_key.append_child(clmn->name.c_str());
					tbl->primary_name=clmn->name;
					break;
					case 2:clmn->node.append_attribute("index").set_value(0);
					unique_key.append_child(clmn->name.c_str());
					tbl->keys[clmn->name];
					break;
					case 3:clmn->node.append_attribute("unique");
					clmn->attr[0]=true;
					unique_key.append_child(clmn->name.c_str());
					tbl->keys[clmn->name];
					break;
					case 4:clmn->node.append_attribute("foreign");
					clmn->attr[4]=true;
					pugi::xml_node foreign_node=foreign_key.append_child (clmn->name.c_str());
					foreign_node.append_attribute("to_tbl").set_value(con->tbl_name_to->c_str());
					foreign_node.append_attribute("to_clmn").set_value(con->to_list->at(0)->c_str());
					tbl->foreign_keys.insert({clmn->name,{*(con->tbl_name_to),*(con->to_list->at(0))}});
					break;
				}
			}
		}
	}
	tbl->node.append_attribute("count").set_value(col_cnt);
	tbl->col_cnt=col_cnt;
}
void Idx_create::check(Data *d)
{
	Database *db=static_cast<Database*>(d);
	auto it=db->tables.find(*tbl_name);
	if(it==db->tables.end())
	{
		error=true;
		error_msg="Table does not exist";
		return;
	}
	Table *tbl=it->second;
	s="";
	for(int i=0;i<col_list->size();i++)
	{
		if(tbl->columns.find(*(col_list->at(i)))==tbl->columns.end())
		{
			error=true;
			error_msg="Column does not exist";
			return;
		}
		s+=*(col_list->at(i))+"-";
	}
	if(col_list->size()==1)
		s=s.substr(0,s.length()-1);
	if(tbl->keys.find(s.c_str())!=tbl->keys.end())
	{
		error=true;
		error_msg="Index already exist with these columns";
		return;
	}
}
void Idx_create::execute(Data *d)
{
	Database *db=static_cast<Database*>(d);
	Table *tbl=db->tables[*tbl_name];
	if(col_list->size()>1)
	{
		pugi::xml_node node=tbl->node.child("attributes").append_child(s.c_str());
		node.append_attribute("unique");
		tbl->keys[s];
	}
	else
	{
		tbl->node.child(s.c_str()).append_attribute("unique");
		tbl->keys[s];
	}
}
void View_create::check(Data *d)
{
	
}
void View_create::execute(Data *d)
{
	
}
void Insert_stmt::check(Data *d)
{
	Database *db=static_cast<Database*>(d);
	auto it=db->tables.find(*tbl_name);
	if(it==db->tables.end())
	{
		error=true;
		error_msg="Table does not exist";
		return;
	}
	Table* tbl=it->second;
	if(cols==NULL)
	{
		pugi::xml_node clmn=tbl->node.child("columns");
		for(auto i=clmn.begin();i!=clmn.end();i++)
		{
			Column *clmn=tbl->columns[i->name()];
			if(clmn->attr[2])
			{
				auto_inc=clmn;
			}
			else if(clmn->attr[1])
				checker.push_back({clmn->idx,clmn->datatype,&(tbl->primary),false});
			else if(clmn->attr[4])
			{
				Table* tbl1=db->tables[tbl->foreign_keys[clmn->name].first];
				Column* clmn1=tbl1->columns[tbl->foreign_keys[clmn->name].second];
				if(clmn1->attr[1])
				{
					checker.push_back({clmn->idx,clmn->datatype,&(tbl1->primary),true});
				}
				else
					checker.push_back({clmn->idx,clmn->datatype,&(tbl1->keys[clmn1->name]),true});
			}
			else if(clmn->attr[0])
				checker.push_back({clmn->idx,clmn->datatype,&(tbl->keys[clmn->name]),false});
			else
				checker.push_back({clmn->idx,clmn->datatype,NULL,false});
		}
	}
	else
	{
		bool primary_given=false;
		for(int i=0;i<cols->size();i++)
		{
			auto it=tbl->columns.find(*(cols->at(i)));
			if(it==tbl->columns.end())
			{
				error=true;
				error_msg="Columns does not exist";
				return;
			}
			Column *clmn=it->second;
			if(clmn->attr[2])
			{
				error=true;
				error_msg="Cannot insert into Auto increment Column";
				return;
			}
			else if(clmn->attr[1])
			{
				checker.push_back({clmn->idx,clmn->datatype,&(tbl->primary),false});
				primary_given=true;
			}
			else if(clmn->attr[4])
			{
				Table* tbl1=db->tables[tbl->foreign_keys[clmn->name].first];
				Column* clmn1=tbl1->columns[tbl->foreign_keys[clmn->name].second];
				if(clmn1->attr[1])
					checker.push_back({clmn->idx,clmn->datatype,&(tbl1->primary),true});
				else
					checker.push_back({clmn->idx,clmn->datatype,&(tbl1->keys[clmn1->name]),true});
			}
			else if(clmn->attr[0])
				checker.push_back({clmn->idx,clmn->datatype,&(tbl->keys[clmn->name]),false});
			else
				checker.push_back({clmn->idx,clmn->datatype,NULL,false});
		}
		if(!primary_given)
		{
			error=true;
			error_msg="Primary Key data not given";
			return;
		}
	}
	for(int i=0;i<data->size();i++)
	{
		vector<Data_val*>* vec=data->at(i);
		if(vec->size()!=checker.size())
		{
			error=true;
			error_msg="Data list size does not match Column list size";
			return;
		}
		for(int j=0;j<checker.size();j++)
		{
			if(checker[j].datatype!=vec->at(j)->type)
			{
				error=true;
				error_msg="Datatype mismatch";
				return;
			}
			if(checker[j].key)
			{
				string s;
				switch(vec->at(j)->type)
				{
					case 1:s=to_string(vec->at(j)->x.int_val);
					break;
					case 2:s=to_string(vec->at(j)->x.dbl_val);
					break;
					case 3:
					case 4:s=*(vec->at(j)->x.s);
					break;
				}
				auto it1=checker[j].key->find(s);
				if(!checker[j].foreign)
				{
					if(it1!=checker[j].key->end())
					{
						error=true;
						error_msg="Value already present";
						return;
					}
				}
				else
				{
					if(it1==checker[j].key->end())
					{
						error=true;
						error_msg="Foreign key not found";
						return;
					}
				}
			}
		}
	}
}
void Insert_stmt::execute(Data *d)
{
	Database *db=static_cast<Database*>(d);
	Table* tbl=db->tables[*tbl_name];
	rowno=tbl->rowcnt;
	int oldrowno=rowno;
	pkcnt=tbl->pkcnt;
	tbl_idx=tbl->idx;
	libxl::Sheet *sheet=tbl->sheet;
	for(int i=0;i<data->size();i++)
	{
		vector<Data_val*>* vec=data->at(i);
		rowno++;
		pkcnt++;
		if(auto_inc)
		sheet->writeNum(rowno,auto_inc->idx,pkcnt);
		for(int j=0;j<vec->size();j++)
		{
			switch(vec->at(j)->type)
			{
				case 1:sheet->writeNum(rowno,checker[j].idx,vec->at(j)->x.int_val);
				if(checker[j].key)
				{
					checker[j].key->insert(to_string(vec->at(j)->x.int_val));
				}
				break;
				case 2:sheet->writeNum(rowno,checker[j].idx,vec->at(j)->x.dbl_val);
				if(checker[j].key)
				{
					checker[j].key->insert(to_string(vec->at(j)->x.dbl_val));
				}
				break;
				case 3:
				case 4:sheet->writeStr(rowno,checker[j].idx,vec->at(j)->x.s->c_str());
				if(checker[j].key)
				{
					checker[j].key->insert(*(vec->at(j)->x.s));
				}
				break;
			}
		}
	}
	tbl->node.attribute("rowcnt").set_value(rowno);
	tbl->node.attribute("pkcnt").set_value(pkcnt);
	tbl->rowcnt=rowno;
	tbl->pkcnt=pkcnt;
	if(tbl->rows.size()==0)
		tbl->rows.insert({1,rowno});
	else
		tbl->rows.rbegin()->second+=rowno-oldrowno;
	tbl->rows_change=true;
}
void Delete_stmt::check(Data *d)
{
	Database *db=static_cast<Database*>(d);
	auto it=db->tables.find(*tbl_name);
	if(it==db->tables.end())
	{
		error=true;
		error_msg="Table does not exist";
		return;
	}
	if(where_cond&&where_cond->check(it->second))
	{
		error=true;
		error_msg="Error in Where clause";
		return;
	}
	if(orderby_cond&&orderby_cond->check(it->second))
	{
		error=true;
		error_msg="Error in Orderby clause";
		return;
	}
}
void Delete_stmt::execute(Data *d)
{
	Database *db=static_cast<Database*>(d);
	auto it=db->tables.find(*tbl_name);
	Table* tbl=it->second;
	int rowcnt=tbl->rowcnt;
	libxl::Sheet* sheet=tbl->sheet;
	vector<int> res;
	bool unique_col_update;
	for(auto i=tbl->rows.begin();i!=tbl->rows.end();i++)
	{
		int idx=i->first,length=i->second;
		for(int j=idx;j<idx+length;j++)
			res.push_back(j);
	}
	if(where_cond)
	{
		where_cond->execute(tbl,limit);
		if(orderby_cond)
		{
			orderby_cond->res=where_cond->res;
			orderby_cond->execute(tbl);
			res=orderby_cond->res;
		}
		else
			res=where_cond->res;
	}
	else if(orderby_cond)
	{
		orderby_cond->res=res;
		orderby_cond->execute(tbl);
		res=orderby_cond->res;
	}
	map<int,int> vals;
	compress(res,vals);
	cerr<<res.size()<<" "<<vals.size()<<endl;
	for(auto i=tbl->columns.begin();i!=tbl->columns.end();i++)
	{
		if(i->second->attr[1])
			checker.push_back({i->second->datatype,i->second->idx,&tbl->primary});
		else if(i->second->attr[0])
			checker.push_back({i->second->datatype,i->second->idx,&tbl->keys[i->second->name]});
	}
	for(auto i=vals.begin();i!=vals.end();i++)
	{
		int in=i->first,len=i->second;
		if(checker.size()>0)
		{
			for(int k=0;k<checker.size();k++)
			{
				for(int j=in;j<len+in;j++)
				{
					switch(checker[k].datatype)
					{
						case 1:checker[k].key->erase(to_string((int)sheet->readNum(j,checker[k].idx)));
						break;
						case 2:checker[k].key->erase(to_string(sheet->readNum(j,checker[k].idx)));
						break;
						case 3:
						case 4:checker[j].key->erase(string(sheet->readStr(j,checker[k].idx)));
						break;
					}
				}
			}
		}
		tbl->sheet->clear(in,in+len-1,1,tbl->col_cnt);
		auto x=tbl->rows.upper_bound(in);
		x--;
		int oldidx=x->first,oldlen=x->second;
		tbl->rows.erase(x);
		if(in==oldidx)
		{
			if(oldlen-len>0)
			tbl->rows.insert({oldidx+len,oldlen-len});
		}
		else
		{
			if(in-oldidx>0)
			tbl->rows.insert({oldidx,in-oldidx});
			if(oldlen-in-len+1>0)
			tbl->rows.insert({in+len,oldlen-in-len+1});
		}
	}
	tbl->rows_change=true;
}
void Delete_stmt::compress(vector<int> &res,map<int,int> &vals)
{
	sort(res.begin(),res.end());
	int curr=res[0],init=res[0],length=1;
	for(int i=1;i<res.size();i++)
	{
		if(res[i]==curr+1)
		{
			length++;
			curr++;
		}
		else
		{
			vals.insert({init,length});
			init=res[i];
			curr=res[i];
			length=1;
		}
	}
	vals.insert({init,length});
}
void Rename_stmt::check(Data *d)
{
	Database *db=static_cast<Database*>(d);
	for(int i=0;i<list->size();i++)
	{
		if(db->tables.find(*(list->at(i)->first))==db->tables.end())
		{
			error=true;
			error_msg="Table name does not exist";
			return;
		}
	}
}
void Rename_stmt::execute(Data *d)
{
	Database *db=static_cast<Database*>(d);
	for(int i=0;i<list->size();i++)
	{
		db->node.child(list->at(i)->first->c_str()).set_name(list->at(i)->second->c_str());
		auto val=db->tables.extract(*(list->at(i)->first));
		val.key()=*(list->at(i)->second);
		db->tables.insert(move(val));
		Table* tbl=db->tables[*(list->at(i)->second)];
		tbl->name=*(list->at(i)->second);
		tbl->sheet->setName(list->at(i)->second->c_str());
	}
}
void Alter_stmt::check(Data *d)
{
	
}
void Alter_stmt::execute(Data *d)
{
	
}
void Use_stmt::check(Data *d)
{
	Root *root=static_cast<Root*>(d);
	auto it=root->databases.find(*db_name);
	if(it==root->databases.end())
	{
		error=true;
		error_msg="Database name does not exist";
		return;
	}
}
void Use_stmt::execute(Data *d)
{
	Root *root=static_cast<Root*>(d);
	curdb=root->databases[*db_name];
}
void Db_show::check(Data *d)
{
	
}
void Db_show::execute(Data *d)
{
	Root *root=static_cast<Root*>(d);
	std::cout<<"\n";
	for(auto it=root->databases.begin();it!=root->databases.end();it++)
		std::cout<<it->first<<"\n";
	std::cout<<"\n";
}
void Tbl_show::check(Data *d)
{
	Root *root=static_cast<Root*>(d);
	if(db_name!=NULL)
	{
		if(root->databases.find(*db_name)==root->databases.end())
		{
			error=true;
			error_msg="Database does not exist";
			return;
		}
	}
	
}
void Tbl_show::execute(Data *d)
{
	Root *root=static_cast<Root*>(d);
	Database *db;
	if(db_name==NULL)
		db=curdb;
	else
		db=root->databases[*db_name];
	std::cout<<"\n";
	for(auto it=db->tables.begin();it!=db->tables.end();it++)
		std::cout<<it->first<<"\n";
	std::cout<<"\n";
}
void Clmns_show::check(Data *d)
{
	if(tbl_name==NULL)
	{
		error=true;
		error_msg="Table name not provided";
		return;
	}
	Root *root=static_cast<Root*>(d);
	Database *db;
	if(db_name==NULL)
		db=curdb;
	else
	{
		auto it=root->databases.find(*db_name);
		if(it==root->databases.end())
		{
			error=true;
			error_msg="Database does not exist";
			return;
		}
		db=it->second;
	}
	auto it=db->tables.find(*tbl_name);
	if(it==db->tables.end())
	{
		error=true;
		error_msg="Table does not exist";
	}
}
void Clmns_show::execute(Data *d)
{
	Root *root=static_cast<Root*>(d);
	Database *db;
	if(db_name==NULL)
		db=curdb;
	else
		db=root->databases[*db_name];
	Table *tbl=db->tables[*tbl_name];
	std::cout<<"\n";
	for(auto it=tbl->columns.begin();it!=tbl->columns.end();it++)
		std::cout<<it->first<<"\n";
	std::cout<<"\n";
}