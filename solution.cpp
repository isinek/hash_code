#include <cstdlib>
#include <iostream>
#include <vector>
#include <map>
#include <utility>
#include <algorithm>
#include <cmath>
#include <iterator>

#define dump(...)			cerr << "[" << #__VA_ARGS__ ": " << (__VA_ARGS__) << "]" << endl
#define arr_dump(...)		cerr << "[" << #__VA_ARGS__ "(" << sizeof((__VA_ARGS__))/sizeof((__VA_ARGS__)[0]) << "): ["; for (unsigned long long int it = 0; it < sizeof((__VA_ARGS__))/sizeof((__VA_ARGS__)[0]); ++it) cerr << (__VA_ARGS__)[it] << (it + 1 < sizeof((__VA_ARGS__))/sizeof((__VA_ARGS__)[0]) ? ", " : ""); cerr << "]]" << endl
#define darr_dump(n, ...)	cerr << "[" << #__VA_ARGS__ "(" << n << "): ["; for (unsigned long long int it = 0; it < n; ++it) cerr << (__VA_ARGS__)[it] << (it + 1 < n ? ", " : ""); cerr << "]]" << endl
#define vec_dump(...)		cerr << "[" << #__VA_ARGS__ "(" << (__VA_ARGS__).size() << "): ["; for (auto it = (__VA_ARGS__).begin(); it != (__VA_ARGS__).end(); ++it) cerr << *it << (it + 1 != (__VA_ARGS__).end() ? ", " : ""); cerr << "]]" << endl
#define pair_dump(...)		cerr << "[" << #__VA_ARGS__ ": (" << (__VA_ARGS__).first << ", " << (__VA_ARGS__).second << ")]" << endl
#define vec_pair_dump(...)	cerr << "[" << #__VA_ARGS__ "(" << (__VA_ARGS__).size() << "): ["; for (auto it = (__VA_ARGS__).begin(); it != (__VA_ARGS__).end(); ++it) cerr << "(" << it->first << ", " << it->second << ")" << (it + 1 != (__VA_ARGS__).end() ? ", " : ""); cerr << "]]" << endl

using namespace std;

class Contributor;

class Project {
	private:
		string name;
		unsigned int daysToComplete;
		unsigned int award;
		unsigned int bestBeforeDay;
		vector<string> rolesOrder;

	public:
		map<string, unsigned short> Roles;
		map<string, Contributor*> Contributors;
		unsigned int DayStarted;

		Project(string name, unsigned int daysToComplete, unsigned int award, unsigned int bestBeforeDay) {
			this->name = name;
			this->daysToComplete = daysToComplete;
			this->award = award;
			this->bestBeforeDay = bestBeforeDay;
			this->Roles.clear();
			this->DayStarted = ~0;
			rolesOrder.clear();
		}

		friend ostream& operator<<(ostream &stream, Project &p);

		bool operator<(Project &o) {
			return this->bestBeforeDay < o.bestBeforeDay || (this->bestBeforeDay == o.bestBeforeDay && this->daysToComplete < this->bestBeforeDay);
		}

		bool operator>(Project &o) {
			return this->bestBeforeDay > o.bestBeforeDay || (this->bestBeforeDay == o.bestBeforeDay && this->daysToComplete > this->bestBeforeDay);
		}

		void AddRole(string name, unsigned short level) {
			this->Roles[name] = level;
			this->rolesOrder.push_back(name);
		}

		void AddContributor(string role, Contributor *contributor) {
			this->Contributors[role] = contributor;
		}

		unsigned int GetDaysToComplete(void) {
			return this->daysToComplete;
		}

		bool IsCompleted(void) {
			for (map<string, unsigned short>::iterator it = this->Roles.begin(); it != this->Roles.end(); ++it)
				if (this->Contributors.find(it->first) == this->Contributors.end())
					return false;
			return true;
		}
};

class Contributor {
	private:
		string name;
		map<string, unsigned short> skills;
		vector<Project*> projects;

	public:
		Contributor(string name) {
			this->name = name;
			this->skills.clear();
		}

		friend ostream& operator<<(ostream &stream, Contributor &c) {
			stream << "Contributor: " << c.name << endl;
			stream << "  Skills:" << endl;
			for (map<string, unsigned short>::iterator it = c.skills.begin(); it != c.skills.end(); ++it)
				stream << "    " << it->first << " " << it->second << endl;
			return stream;
		}

		string GetName(void) {
			return this->name;
		}

		unsigned short GetSkillLevel(string skill) {
			return this->skills[skill];
		}

		void AddSkill(string name, unsigned short level) {
			this->skills[name] = level;
		}

		void AddProject(Project *project) {
			this->projects.push_back(project);
		}

		pair<bool, string> CanWorkOnProject(Project *project) {
			pair<bool, string> ret(false, "");

			for (map<string, unsigned short>::iterator it = project->Roles.begin(); it != project->Roles.end(); ++it) {
				if (project->Contributors.find(it->first) != project->Contributors.end()) {
					continue;
				} else if (this->skills.find(it->first) != this->skills.end() && it->second <= this->skills[it->first]) {
					ret.second = it->first;
					break;
				}
			}

			if (ret.second == "")
				return ret;

			for (vector<Project*>::iterator it = this->projects.begin(); it != this->projects.end(); ++it)
				if (((*it)->DayStarted <= project->DayStarted && (*it)->DayStarted + (*it)->GetDaysToComplete() >= project->DayStarted) ||
					((*it)->DayStarted >= project->DayStarted && (*it)->DayStarted <= project->DayStarted + project->GetDaysToComplete()))
						return ret;

			ret.first = true;
			return ret;
		}

		pair<bool, string> CanLearnOnProject(Project *project) {
			pair<bool, string> ret(false, "");

			for (map<string, unsigned short>::iterator it = project->Roles.begin(); it != project->Roles.end(); ++it) {
				if (project->Contributors.find(it->first) != project->Contributors.end()) {
					continue;
				} else if (this->skills.find(it->first) != this->skills.end() && it->second <= this->skills[it->first]) {
					ret.second = it->first;
					break;
				}
			}

			if (ret.second == "")
				return ret;

			for (vector<Project*>::iterator it = this->projects.begin(); it != this->projects.end(); ++it)
				if (((*it)->DayStarted <= project->DayStarted && (*it)->DayStarted + (*it)->GetDaysToComplete() >= project->DayStarted) ||
					((*it)->DayStarted >= project->DayStarted && (*it)->DayStarted <= project->DayStarted + project->GetDaysToComplete()))
						return ret;

			ret.first = true;
			return ret;
		}

		void LevelUpSkill(string skill) {
			if (this->skills[skill] < 10)
				++this->skills[skill];
		}
};

ostream& operator<<(ostream &stream, Project &p) {
	/*stream << "Project: " << p.name << endl;
	stream << "  Day of start: " << p.DayStarted << endl;
	stream << "  Days to complete: " << p.daysToComplete << endl;
	stream << "  Award: " << p.award << endl;
	stream << "  Best complete in: " << p.bestBeforeDay << endl;
	stream << "  Roles:" << endl;
	for (map<string, unsigned short>::iterator it = p.Roles.begin(); it != p.Roles.end(); ++it) {
		stream << "    " << it->first << " " << it->second;
		if (p.Contributors.find(it->first) != p.Contributors.end())
			stream << " (" << p.Contributors[it->first]->GetName() << ")";
		stream << endl;
	}*/

	/******
	 * Final printout
	 ******/

	stream << p.name << endl;
	for (vector<string>::iterator it = p.rolesOrder.begin(); it != p.rolesOrder.end(); ++it) {
		if (p.Contributors.find(*it) != p.Contributors.end())
			stream << p.Contributors[*it]->GetName();
		if (next(it) != p.rolesOrder.end())
			stream << " ";
	}

	return stream;
}

void LevelUpContributors(Project *project) {
	for (map<string, Contributor*>::iterator it = project->Contributors.begin(); it != project->Contributors.end(); ++it) {
		if (project->Roles[it->first] >= it->second->GetSkillLevel(it->first)) {
			it->second->LevelUpSkill(it->first);
		}
	}
}

int main() {
	unsigned int nContributors, nProjects;
	string name;
	unsigned int n, level, d, s, b;
	vector<Contributor> contributors;
	vector<Project> projects;
	pair<bool, string> canWorkOnProject;
	vector<Project*> finishedProjects;
	vector<Project*> pendingProjects;
	unsigned int endDayOfLastProject = 0;

	cin >> nContributors >> nProjects;
	for (unsigned int i = 0; i < nContributors; ++i) {
		cin >> name >> n;
		contributors.push_back(Contributor(name));
		for (unsigned int j = 0; j < n; ++j) {
			cin >> name >> level;
			contributors[i].AddSkill(name, level);
		}
	}
	for (unsigned int i = 0; i < nProjects; ++i) {
		cin >> name >> d >> s >> b >> n;
		projects.push_back(Project(name, d, s, b));
		for (unsigned int j = 0; j < n; ++j) {
			cin >> name >> level;
			projects[i].AddRole(name, level);
		}
	}

	sort(projects.begin(), projects.end());

	for (unsigned int p = 0; p < nProjects; ++p)
		pendingProjects.push_back(&projects[p]);

	for (unsigned int d = 0; d <= endDayOfLastProject + 100 && !pendingProjects.empty(); ++d) {
		Project *currProject = pendingProjects[0];
		pendingProjects.erase(pendingProjects.begin());

		currProject->DayStarted = d;
		for (unsigned int c = 0; c < nContributors; ++c) {
			if (currProject->IsCompleted())
				break;

			canWorkOnProject = contributors[c].CanWorkOnProject(currProject);
			if (canWorkOnProject.first) {
				contributors[c].AddProject(currProject);
				currProject->AddContributor(canWorkOnProject.second, &contributors[c]);
			}
		}
		if (currProject->IsCompleted()) {
			LevelUpContributors(currProject);
			finishedProjects.push_back(currProject);
			if (currProject->DayStarted + currProject->GetDaysToComplete() > endDayOfLastProject)
				endDayOfLastProject = currProject->DayStarted + currProject->GetDaysToComplete();
		} else {
			currProject->DayStarted = ~0;
			pendingProjects.push_back(currProject);
		}
	}

	cout << finishedProjects.size() << endl;
	for (vector<Project*>::iterator it = finishedProjects.begin(); it != finishedProjects.end(); ++it)
		cout << (*(*it)) << endl;

	return 0;
}
