#pragma once

#include <Entity/Account.h>
#include <DAO/DAO.h>
#include <System/Log.h>

namespace Framework{
	namespace DAO
	{
		template <>
		inline void DAO<Skyrim::Entity::Account>::Load(SimpleDB::Database& pDatabase)
		{
			try
			{
				std::ostringstream oss;
				oss << "SELECT userid, password, username, username, usergroupid FROM user WHERE username='" << pDatabase.escapeString(mEntity.User)
					<< "' AND password=MD5(CONCAT(MD5('" << pDatabase.escapeString(mEntity.Pass) << "'), salt))";

				SimpleDB::Query query(pDatabase);
				SimpleDB::StringColumn pass(33), user(61), nicename(61);
				SimpleDB::IntColumn id,level;
				SimpleDB::Column * cols[] = {&id,&pass,&user,&nicename,&level};
				query.bind(cols,5);
				query.execute(oss.str());

				if(query.fetchRow())
				{
					mEntity.Pass = pass.value();
					mEntity.User = user.value();
					mEntity.Id = id.value();
					mEntity.Level = level.value()==6?10:0;
					mEntity.Nicename = nicename.value();

					OnEvent(IDAO::LOAD, true);
				}
				else
					throw std::runtime_error("Account not found");
			}
			catch(std::exception& e)
			{
				System::Log::GetInstance()->Error(e.what());
				OnEvent(IDAO::LOAD, false);
			}
		}

		template <>
		inline void DAO<Skyrim::Entity::Account>::Save(SimpleDB::Database& pDatabase)
		{
			try
			{
				/*std::ostringstream oss;
				oss << "UPDATE realm_accounts SET ticket='" << mEntity._ticket << "' WHERE guid='" << mEntity._id << "'";
				pDatabase.voidQuery(oss.str());*/
			}
			catch(std::exception& e)
			{
				System::Log::GetInstance()->Error(e.what());
			}
		}
	}
}