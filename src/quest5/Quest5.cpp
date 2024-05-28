std::string getKeyWithMaxValue(std::map<std::string, int> &thisMap)
{
    std::string maxKey = thisMap.begin()->first;
    int maxValue = thisMap.begin()->second;

    // Iterate through the map to find the key with the maximum value
    for (const auto& pair : thisMap) {
        if (pair.second > maxValue) {
            maxValue = pair.second;
            maxKey = pair.first;
        }
    }
    return maxKey;
}

void setJourney(std::vector<Pedestrian> &listPedestrian, std::vector<Ward> &listWard)
{
    int single = getNumberVisitor(listPedestrian);
    int triple = listPedestrian.size() - single;
    std::vector<std::pair<Ward, int>> pairList = Quest4::OutListWardInt(listWard, triple, single);
    std::map <std::string, int> journeyDictionary;
    for (int i = 0; i < pairList.size(); i++)
    {
        if (journeyDictionary.find(pairList[i].first.getName()) == journeyDictionary.end())
        {
            journeyDictionary.insert(std::make_pair(pairList[i].first.getName(), 1));
        }
        else 
        {
            journeyDictionary[pairList[i].first.getName()] += 1;
        }
    }

    for (int i = 0; i < Quest3::getlistVisitors().size(); i++)
    {
        std::string maxKey = getKeyWithMaxValue(journeyDictionary);
        Quest3::getlistVisitors()[i].set
    }
}