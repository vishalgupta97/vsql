#include "tree.h"
void Cond_exp::check(pugi::xml_node &tbl_node)
{
	pugi::xml_node clmn=tbl_node.child(lhs->c_str());
	if(clmn==NULL||clmn.attribute("datatype").as_int()!=rhs->type)
	{
			error=true;
			printf("this one\n");
			return;
	}
	if((op_type!=1&&op_type!=6)&&(rhs->type==3||rhs->type==4))
	{
		error=true;
		printf("that one\n");
		return;
	}
	col_idx=clmn.attribute("index").as_int();
}
std::string Cond_exp::gen(int &cnt,Where_stmt* stmt)
{
	stmt->exps.push_back(this);
	string s="t"+to_string(cnt);
	cnt++;
	return s;
}
void And_exp::check(pugi::xml_node &tbl_node)
{
	lhs->check(tbl_node);
	if(lhs->error)
		error=true;
	else
	{
		rhs->check(tbl_node);
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
void Or_exp::check(pugi::xml_node &tbl_node)
{
	lhs->check(tbl_node);
	if(lhs->error)
		error=true;
	else
	{
		rhs->check(tbl_node);
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
bool Where_stmt::check(pugi::xml_node tbl_clmns)
{
	exp->check(tbl_clmns);
	return exp->error;
}
void Where_stmt::execute(pugi::xml_node tbl_node,libxl::Sheet* &sheet)
{
	int cnt=0,rowno=tbl_node.attribute("rowcnt").as_int();
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
					case 1:temp=sheet->readNum(i,exps[j]->col_idx)==exps[j]->rhs->x.int_val;
					break;
					case 2:temp=sheet->readNum(i,exps[j]->col_idx)==exps[j]->rhs->x.dbl_val;
					break;
					case 3:
					case 4:temp=exps[j]->rhs->x.s->compare(sheet->readStr(i,exps[j]->col_idx))==0;
					break;
				}
				break;
				case 2:switch(exps[j]->rhs->type)
				{
					case 1:temp=sheet->readNum(i,exps[j]->col_idx)<exps[j]->rhs->x.int_val;
					break;
					case 2:temp=sheet->readNum(i,exps[j]->col_idx)<exps[j]->rhs->x.dbl_val;
					break;
				}
				break;
				case 3:switch(exps[j]->rhs->type)
				{
					case 1:temp=sheet->readNum(i,exps[j]->col_idx)>exps[j]->rhs->x.int_val;
					break;
					case 2:temp=sheet->readNum(i,exps[j]->col_idx)>exps[j]->rhs->x.dbl_val;
					break;
				}
				break;
				case 4:switch(exps[j]->rhs->type)
				{
					case 1:temp=sheet->readNum(i,exps[j]->col_idx)<=exps[j]->rhs->x.int_val;
					break;
					case 2:temp=sheet->readNum(i,exps[j]->col_idx)<=exps[j]->rhs->x.dbl_val;
					break;
				}
				break;
				case 5:switch(exps[j]->rhs->type)
				{
					case 1:temp=sheet->readNum(i,exps[j]->col_idx)>=exps[j]->rhs->x.int_val;
					break;
					case 2:temp=sheet->readNum(i,exps[j]->col_idx)>=exps[j]->rhs->x.dbl_val;
					break;
				}
				break;
				case 6:switch(exps[j]->rhs->type)
				{
					case 1:temp=sheet->readNum(i,exps[j]->col_idx)!=exps[j]->rhs->x.int_val;
					break;
					case 2:temp=sheet->readNum(i,exps[j]->col_idx)!=exps[j]->rhs->x.dbl_val;
					break;
					case 3:
					case 4:temp=exps[j]->rhs->x.s->compare(sheet->readStr(i,exps[j]->col_idx))!=0;
					break;
				}
				break;
			}
			vals["t"+to_string(j)]=temp;
		}
		if(LibBoolEE::resolve(s,vals))
			res.push_back(i);
	}
}
bool Orderby_stmt::check(pugi::xml_node tbl_clmn)
{
	for(int i=0;i<clmns_list->size();i++)
	{
		pugi::xml_node clmn=tbl_clmn.child(clmns_list->at(i)->first->c_str());
		if(clmn)
			index_type.push_back({clmn.attribute("index").as_int(),clmn.attribute("datatype").as_int()});
		else
			return true;
	}
	return false;
}
void Orderby_stmt::execute(libxl::Sheet* &sheet)
{
	this->sheet=sheet;
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
void Update_stmt::check(pugi::xml_node &db_node,libxl::Book* &book)
{
	pugi::xml_node tbl_clmn=db_node.child(tbl_name->c_str()).child("columns");
	if(tbl_clmn==NULL)
	{
		error=true;
		error_msg="Table does not exist";
		return;
	}
	for(int i=0;i<list->size();i++)
		if(tbl_clmn.child(list->at(i)->first->c_str())==NULL)
		{
			error=true;
			error_msg="Column name does not exist";
			return;
		}
	if(where_cond->check(tbl_clmn))
	{
		error=true;
		error_msg="Error in Where clause";
		return;
	}
	if(orderby_cond->check(tbl_clmn))
	{
		error=true;
		error_msg="Error in Orderby clause";
		return;
	}
}
void Update_stmt::execute(pugi::xml_node &db_node,libxl::Book* &book)
{
	
}
void Select_stmt::check(pugi::xml_node &db_node,libxl::Book* &book)
{
	pugi::xml_node tbl_clmn=db_node.child(tbl_name->c_str()).child("columns");
	if(tbl_clmn==NULL)
	{
		error=true;
		error_msg="Table does not exist";
		return;
	}
	if(col_list)
	{
		for(int i=0;i<col_list->size();i++)
		{
			pugi::xml_node clmn=tbl_clmn.child(col_list->at(i)->c_str());
			if(clmn==NULL)
			{
				error=true;
				error_msg="Column name does not exist";
				return;
			}
			else
			{
				index_type.push_back({clmn.attribute("index").as_int(),clmn.attribute("datatype").as_int()});
			}
		}
	}
	if(where_cond&&where_cond->check(tbl_clmn))
	{
		error=true;
		error_msg="Error in Where clause";
		return;
	}
	if(orderby_cond&&orderby_cond->check(tbl_clmn))
	{
		error=true;
		error_msg="Error in Orderby clause";
		return;
	}
}
void Select_stmt::execute(pugi::xml_node &db_node,libxl::Book* &book)
{
	pugi::xml_node tbl=db_node.child(tbl_name->c_str());
	int rowcnt=tbl.attribute("rowcnt").as_int(),tbl_idx=tbl.attribute("index").as_int();
	libxl::Sheet* sheet=book->getSheet(tbl_idx);
	if(sheet)
	{
		
	}
	else
	{
		printf("%d no\n",tbl_idx);
		return;
	}
	vector<int> res;
	for(int i=1;i<=rowcnt;i++)
		res.push_back(i);
	if(where_cond)
	{
		where_cond->execute(tbl,sheet);
		if(orderby_cond)
		{
			orderby_cond->res=where_cond->res;
			orderby_cond->execute(sheet);
			res=orderby_cond->res;
		}
		else
			res=where_cond->res;
	}
	else if(orderby_cond)
	{
		orderby_cond->res=res;
		orderby_cond->execute(sheet);
		res=orderby_cond->res;
	}
	pugi::xml_node tbl_clmn=tbl.child("columns");
	int cols_count=tbl_clmn.attribute("count").as_int();
	if(!col_list)
	{
		for(auto i=tbl_clmn.begin();i!=tbl_clmn.end();i++)
		{
			index_type.push_back({(*i).attribute("index").as_int(),(*i).attribute("datatype").as_int()});
		}
	}
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
void Db_drop::check(pugi::xml_node &db_node,libxl::Book* &book)
{
	if(db_name==NULL)
	{
		error=true;
		error_msg="Database name not provided";
		return;
	}
	if(curdb&&db_name->compare(curdb.name())==0)
	{
		error=true;
		error_msg="Cannot drop current db";
		return;
	}
	n_db_node=db_node.child(db_name->c_str());
	if(n_db_node==NULL)
	{
		error=true;
		error_msg="Database name does not exist";
	}
}
void Db_drop::execute(pugi::xml_node &db_node,libxl::Book* &book)
{
	remove(db_name->append(".xls").c_str());
	db_node.remove_child(n_db_node);
}
void Tbl_drop::check(pugi::xml_node &db_node,libxl::Book* &book)
{
	for(int i=0;i<tbl_list->size();i++)
		if(db_node.child(tbl_list->at(i)->c_str())==NULL)
		{
			error=true;
			error_msg="Table name does not exist";
			return;
		}
}
void Tbl_drop::execute(pugi::xml_node &db_node,libxl::Book* &book)
{
	for(int i=0;i<tbl_list->size();i++)
	{
		book->delSheet(atoi(db_node.child(tbl_list->at(i)->c_str()).attribute("index").value()));
		db_node.remove_child(tbl_list->at(i)->c_str());
	}
}
void Idx_drop::check(pugi::xml_node &db_node,libxl::Book* &book)
{
	
}
void Idx_drop::execute(pugi::xml_node &db_node,libxl::Book* &book)
{
	
}
void View_drop::check(pugi::xml_node &db_node,libxl::Book* &book)
{
	
}
void View_drop::execute(pugi::xml_node &db_node,libxl::Book* &book)
{
	
}
void Db_create::check(pugi::xml_node &db_node,libxl::Book* &book)
{
	if(!db_name)
	{
		error=true;
		error_msg="Database name not provided";
		return;
	}
	pugi::xml_node node=db_node.child(db_name->c_str());
	if(node)
	{
		error=true;
		error_msg="Database already exist";
	}
}
void Db_create::execute(pugi::xml_node &db_node,libxl::Book* &book)
{
	libxl::Book* n_book=xlCreateBook();
	pugi::xml_node node=db_node.append_child(db_name->c_str());
	n_book->addSheet(string("Sheet1").c_str());
	n_book->save(db_name->append(".xls").c_str());
	n_book->release();
	pugi::xml_attribute atr=node.append_attribute("count");
	atr.set_value("0");
}
void Tbl_create::check(pugi::xml_node &db_node,libxl::Book* &book)
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
	if(db_node.child(tbl_name->c_str()))
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
						case 2:auto_inc=cd->col_name;
						case 3:if(primary_key)
								{
									error=true;
									error_msg="Primary Key already defined";
									return;
								}
								else
								primary_key=true;
							break;
						case 5:if(db_node.child(cd->list->at(i)->tbl_name->c_str()).child("columns").child(cd->list->at(i)->col_name->c_str()).attribute("unique")==NULL)
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
				pugi::xml_node to_tbl=db_node.child(con->tbl_name_to->c_str());
				if(to_tbl==NULL)
				{
					error=true;
					error_msg="Foreign Table does not exist";
					return;
				}
				string s="";
				for(int j=0;j<con->to_list->size();j++)
				{
					if(!bfl->chk_hash(con->col_list->at(j)->c_str())||to_tbl.child(con->to_list->at(j)->c_str())==NULL)
					{
						error=true;
						error_msg="Column does not exist";
						return;
					}
					else
					{
						s+=*(con->to_list->at(i))+"-";
					}
				}
				if(to_tbl.child(s.c_str()).attribute("unique")==NULL)
				{
					error=true;
					error_msg="Foreign Key Columns are not unique";
					return;
				}
			}
		}
	}	
}
void Tbl_create::execute(pugi::xml_node &db_node,libxl::Book* &book)
{
	pugi::xml_node tbl=db_node.append_child(tbl_name->c_str());
	pugi::xml_attribute atr=tbl.append_attribute("index");
	atr.set_value(db_node.attribute("count").as_int()+1);
	db_node.attribute("count").set_value(atr.value());
	atr=tbl.append_attribute("rowcnt");
	atr.set_value("0");
	book->addSheet(tbl_name->c_str());
	pugi::xml_node clmns=tbl.append_child("columns");
	pugi::xml_node attrs=tbl.append_child("attributes");
	int col_cnt=0;
	for(int i=0;i<list->size();i++)
	{
		if(list->at(i)->type==1)
		{
			col_cnt++;
			Col_def* cd=list->at(i)->x.cd;
			pugi::xml_node clmn=clmns.append_child(cd->col_name->c_str());
			pugi::xml_attribute atr_type=clmn.append_attribute("datatype");
			atr_type.set_value(datatype_vals[*(cd->datatype)].c_str());
			pugi::xml_attribute atr_index=clmn.append_attribute("index");
			atr_index.set_value(to_string(i+1).c_str());
			bool not_null=false,ainc=false,primary=false,unique=false,foreign=false;
			Special_ele *se=NULL;
			if(cd->list)
			{
				for(int j=0;j<cd->list->size();j++)
				{
					switch(cd->list->at(j)->type)
					{
						case 1:not_null=true;break;
						case 2:ainc=true;break;
						case 3:primary=true;not_null=true;ainc=true;unique=true;break;
						case 4:unique=true;break;
						case 5:foreign=true;se=cd->list->at(j);break;
					}
				}
			}
			if(unique)
				clmn.append_attribute("unique");
			if(primary)
			{
				clmn.append_attribute("primary");
				if(atr_type.as_int()==1)
				{
					tbl.append_attribute("pkcnt").set_value(0);//primary key counter
				}
			}
			if(ainc)
				clmn.append_attribute("auto_inc");
			if(not_null)
				clmn.append_attribute("not_null");
			if(foreign)
			{
				clmn.append_attribute("foreign");
				pugi::xml_attribute atr=clmn.append_attribute("to_tbl");
				atr.set_value(se->tbl_name->c_str());
				atr=clmn.append_attribute("to_clmn");
				atr.set_value(se->col_name->c_str());
				
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
				pugi::xml_node chld=attrs.append_child(s.c_str());
				switch(con->type)
				{
					case 1:chld.append_attribute("unique");
					chld.append_attribute("primary");
					break;
					case 2:chld.append_attribute("index");
					break;
					case 3:chld.append_attribute("unique");
					case 4:pugi::xml_attribute atr=chld.append_attribute("foreign_tbl");
					atr.set_value(con->tbl_name_to->c_str());
					string y="";
					for(int j=0;j<con->to_list->size();j++)
						y+=*(con->to_list->at(j))+"-";
					atr=chld.append_attribute("foreign_clmn");
					atr.set_value(y.c_str());
				}
			}
			else
			{
				pugi::xml_node chld=tbl.child(con->col_list->at(0)->c_str());
				switch(con->type)
				{
					case 1:chld.append_attribute("unique");
					chld.append_attribute("primary");
					chld.append_attribute("auto_inc");
					chld.append_attribute("not_null");
					if(chld.attribute("datatype").as_int()==1)
					{
						tbl.append_attribute("pkcnt").set_value(0);//primary key counter
					}
					break;
					case 2:chld.append_attribute("index");break;
					case 3:chld.append_attribute("unique");
					case 4:chld.append_attribute("foreign");
					pugi::xml_attribute atr=chld.append_attribute("to_tbl");
					atr.set_value(con->tbl_name_to->c_str());
					atr=chld.append_attribute("to_clmn");
					atr.set_value(con->to_list->at(0)->c_str());
					break;
				}
			}
		}
	}
	clmns.append_attribute("count").set_value(col_cnt);
}
void Idx_create::check(pugi::xml_node &db_node,libxl::Book* &book)
{
	pugi::xml_node tbl_clmn=db_node.child(tbl_name->c_str()).child("columns");
	if(tbl_clmn==NULL)
	{
		error=true;
		error_msg="Table does not exist";
		return;
	}
	s="";
	for(int i=0;i<col_list->size();i++)
	{
		if(tbl_clmn.child(col_list->at(i)->c_str())==NULL)
		{
			error=true;
			error_msg="Column does not exist";
			return;
		}
		s+=*(col_list->at(i))+"-";
	}
	if(db_node.child(tbl_name->c_str()).child("attributes").child(s.c_str())!=NULL)
	{
		error=true;
		error_msg="Index already exist with these columns";
		return;
	}
}
void Idx_create::execute(pugi::xml_node &db_node,libxl::Book* &book)
{
	if(col_list->size()>1)
	{
		pugi::xml_node node=db_node.child(tbl_name->c_str()).child("attributes").append_child(s.c_str());
		node.append_attribute("unique");
		if(idx_name)
		{
			pugi::xml_attribute atr=node.append_attribute("name");
			atr.set_value(idx_name->c_str());
		}
	}
	else 
	{
		
	}
}
void View_create::check(pugi::xml_node &db_node,libxl::Book* &book)
{
	
}
void View_create::execute(pugi::xml_node &db_node,libxl::Book* &book)
{
	
}
void Insert_stmt::check(pugi::xml_node &db_node,libxl::Book* &book)
{
	tbl=db_node.child(tbl_name->c_str());
	pugi::xml_node tbl_clmn=tbl.child("columns");
	if(tbl_clmn==NULL)
	{
		error=true;
		error_msg="Column does not exist";
		return;
	}
	if(cols==NULL)
	{
		for(auto i=tbl_clmn.begin();i!=tbl_clmn.end();i++)
		{
			if((*i).attribute("primary")==NULL)
			{
				checker.push_back((*i).attribute("datatype").as_int());
				indexes.push_back((*i).attribute("index").as_int());
			}
		}
	}
	else
	{
		for(int i=0;i<cols->size();i++)
		{
			pugi::xml_node clmn=tbl_clmn.child(cols->at(i)->c_str());
			if(clmn==NULL)
			{
				error=true;
				error_msg="Columns does not exist";
				return;
			}
			checker.push_back(clmn.attribute("datatype").as_int());
			indexes.push_back(clmn.attribute("index").as_int());
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
			if(checker[j]!=vec->at(j)->type)
			{
				error=true;
				error_msg="Datatype mismatch";
				return;
			}
		}
	}
	rowno=tbl.attribute("rowcnt").as_int();
	pkcnt=tbl.attribute("pkcnt").as_int();
	tbl_idx=tbl.attribute("index").as_int();
	pkindex=tbl_clmn.find_child_by_attribute("auto_inc","").attribute("index").as_int();
	printf("%d\n",pkindex);
}
void Insert_stmt::execute(pugi::xml_node &db_node,libxl::Book* &book)
{
	libxl::Sheet *sheet=book->getSheet(tbl_idx);
	for(int i=0;i<data->size();i++)
	{
		vector<Data_val*>* vec=data->at(i);
		rowno++;
		pkcnt++;
		sheet->writeNum(rowno,pkindex,pkcnt);
		for(int j=0;j<vec->size();j++)
		{
			switch(vec->at(j)->type)
			{
				case 1:sheet->writeNum(rowno,indexes[j],vec->at(j)->x.int_val);
				break;
				case 2:sheet->writeNum(rowno,indexes[j],vec->at(j)->x.dbl_val);break;
				case 3:sheet->writeStr(rowno,indexes[j],vec->at(j)->x.s->c_str());break;
				case 4:sheet->writeStr(rowno,indexes[j],vec->at(j)->x.s->c_str());break;
			}
		}
	}
	tbl.attribute("rowcnt").set_value(rowno);
	tbl.attribute("pkcnt").set_value(pkcnt);
}
void Delete_stmt::check(pugi::xml_node &db_node,libxl::Book* &book)
{
	pugi::xml_node tbl_clmn=db_node.child(tbl_name->c_str()).child("columns");
	if(tbl_clmn==NULL)
	{
		error=true;
		error_msg="Table does not exist";
		return;
	}
	if(where_cond&&where_cond->check(tbl_clmn))
	{
		error=true;
		error_msg="Error in Where clause";
		return;
	}
	if(orderby_cond&&orderby_cond->check(tbl_clmn))
	{
		error=true;
		error_msg="Error in Orderby clause";
		return;
	}
}
void Delete_stmt::execute(pugi::xml_node &db_node,libxl::Book* &book)
{
	libxl::Sheet* sheet=book->getSheet(1);
	sheet->removeRow(3,3);
}
void Rename_stmt::check(pugi::xml_node &db_node,libxl::Book* &book)
{
	for(int i=0;i<list->size();i++)
	{
		if(db_node.child(list->at(i)->first->c_str())==NULL)
		{
			error=true;
			error_msg="Table name does not exist";
			return;
		}
	}
}
void Rename_stmt::execute(pugi::xml_node &db_node,libxl::Book* &book)
{
	for(int i=0;i<list->size();i++)
		db_node.child(list->at(i)->first->c_str()).set_name(list->at(i)->second->c_str());
}
void Alter_stmt::check(pugi::xml_node &db_node,libxl::Book* &book)
{
	
}
void Alter_stmt::execute(pugi::xml_node &db_node,libxl::Book* &book)
{
	
}
void Use_stmt::check(pugi::xml_node &db_node,libxl::Book* &book)
{
	if(db_name==NULL)
	{
		error=true;
		error_msg="Database name not provided";
		return;
	}
	n_db_node=db_node.child(db_name->c_str());
	if(n_db_node==NULL)
	{
		error=true;
		error_msg="Database name does not exist";
		return;
	}
}
void Use_stmt::execute(pugi::xml_node &db_node,libxl::Book* &book)
{
	book->save(string(curdb.name()).append(".xls").c_str());
	book->release();
	book=xlCreateBook();
	book->load(string(n_db_node.name()).append(".xls").c_str());
	curdb=n_db_node;
}
void Db_show::check(pugi::xml_node &db_node,libxl::Book* &book)
{
	
}
void Db_show::execute(pugi::xml_node &db_node,libxl::Book* &book)
{
	std::cout<<"\n";
	for(pugi::xml_node node:db_node.children())
		std::cout<<node.name()<<"\n";
	std::cout<<"\n";
}
void Tbl_show::check(pugi::xml_node &db_node,libxl::Book* &book)
{
	if(db_name==NULL)
		n_db_node=curdb;
	else
	n_db_node=db_node.child(db_name->c_str());
	if(n_db_node==NULL)
	{
		error=true;
		error_msg="Database does not exist";
	}
}
void Tbl_show::execute(pugi::xml_node &db_node,libxl::Book* &book)
{
	std::cout<<"\n";
	for(pugi::xml_node node:n_db_node.children())
		std::cout<<node.name()<<"\n";
	std::cout<<"\n";
}
void Clmns_show::check(pugi::xml_node &db_node,libxl::Book* &book)
{
	if(tbl_name==NULL)
	{
		error=true;
		error_msg="Table name not provided";
		return;
	}
	if(db_name!=NULL)
	tbl_node=db_node.child(db_name->c_str()).child(tbl_name->c_str()).child("columns");
	else
	tbl_node=curdb.child(tbl_name->c_str()).child("columns");
	if(tbl_node==NULL)
	{
		error=true;
		error_msg="Database or Table does not exist";
	}
}
void Clmns_show::execute(pugi::xml_node &db_node,libxl::Book* &book)
{
	std::cout<<"\n";
	for(pugi::xml_node node:tbl_node.children())
		std::cout<<node.name()<<"\n";
	std::cout<<"\n";
}