#include<iostream>
#include<vector>
#include<string>
#include<stdlib.h>
#include <bits/stdc++.h> 
#include<fstream>
#include<sstream> 

using namespace std;

vector< vector<double> > ReadOutlets(string filename);
vector<double> ExtractSortedLatOrLong(vector<vector<double> > latlongs, int lat_flag);
vector<double> FindBoundsBinarySearch(vector<double> array, double key);
vector<double> NearestOutlet(vector<vector<double> > latlongs, vector<double> lat_bounds, vector<double> long_bounds, vector<double> key);
vector<double> FetchLatOrLong(vector<vector<double> > latlongs, double lat_or_long, int lat_flag);
vector<double> FetchRSP(double cc, string filename);


int main()
{
    vector<vector<double> > latlongs;

    latlongs=ReadOutlets("OultetsCsvData.csv");
    vector<double> lats, longs;
    vector<double> lat_bounds;
    vector<double> long_bounds;
    vector<double> key, nearest_outlet;
    double input=0;

    /*for(int i=0; i<latlongs.size(); i++)
    {
        cout<<fixed<<setprecision(0)<<latlongs[i][2]<<", ";
        cout<<setprecision(6)<<latlongs[i][0]<<", "<<latlongs[i][1]<<" "<<"\n";
    }*/
    
    lats=ExtractSortedLatOrLong(latlongs, 1);
    longs=ExtractSortedLatOrLong(latlongs, 0);

    cout<<"Enter Latitude of location:";
    cin>>input;
    key.push_back(input);
    cout<<"Enter Longitude of location:";
    cin>>input;
    key.push_back(input);

    lat_bounds=FindBoundsBinarySearch(lats, key[0]);
    long_bounds=FindBoundsBinarySearch(longs, key[1]);

    //cout<<"[LAT]Entered location lies between"<<lat_bounds[0]<<" and "<<lat_bounds[1]<<"\n";
    //cout<<"[LONG]Entered location lies between"<<long_bounds[0]<<" and "<<long_bounds[1]<<"\n";

    nearest_outlet=NearestOutlet(latlongs, lat_bounds, long_bounds, key);
    
    cout<<"\n";
    cout<<"Nearest HP Oultet Customer Code: "<<fixed<<setprecision(0)<<nearest_outlet[2]<<" at ";
    cout<<setprecision(6)<<nearest_outlet[0]<<", "<<nearest_outlet[1]<<" "<<"\n";

    vector<double> rsp;
    rsp=FetchRSP(nearest_outlet[2], "RSPData.csv");

    cout<<"Petrol Price: "<<fixed<<setprecision(2)<<rsp[0]<<"\nDiesel price: "<<rsp[2]<<"\n";   
}

vector< vector<double> > ReadOutlets(string filename)
{
    ifstream outlets;
    outlets.open(filename.c_str(), ios::in);
    vector<vector<double> > outlet_data;
    string line, word;

    while (getline(outlets,line))
    {
        stringstream ss(line);
        vector<double> row;

        //Splitting with delimiter as comma
        while (getline(ss, word, ','))
        {
            row.push_back(atof(word.c_str()));
        }
        outlet_data.push_back(row);
    }
    outlet_data.erase(outlet_data.begin());        
    return outlet_data;        
}

vector<double> FindBoundsBinarySearch(vector<double> array, double key)
{
    int lower=0, upper=(array.size()-1), mid=(lower+upper)/2;
    vector<double> bounds(2,0);

    if(key<array[0])
    {
        bounds[0]=bounds[1]=array[0];
        cout<<"Search Key Out of Array Bounds.\n";
        return bounds;
    }
    else if(key>array[array.size()-1])
    {
        bounds[0]=bounds[1]=array[array.size()-1];
        cout<<"Search Key Out of Array Bounds.\n";
        return bounds;
    }

    while(1)
    {
        mid=(lower+upper)/2;

        if(key<=array[mid])
            upper=mid;
        else
            lower=mid;
        
        if((upper-lower)<=1)
        {
            bounds[0]=array[lower];
            bounds[1]=array[upper];
            return bounds;
        }
    }

}

vector<double> ExtractSortedLatOrLong(vector<vector<double> > latlongs, int lat_flag)
{
    lat_flag = 1-lat_flag;
    vector<double> result;

    for(int i=0; i<latlongs.size(); i++)
        result.push_back(latlongs[i][lat_flag]);
    sort(result.begin(), result.end());

    return result;
}

vector<double> NearestOutlet(vector<vector<double> > latlongs, vector<double> lat_bounds, vector<double> long_bounds, vector<double> key)
{
    vector<vector<double> > border_points;

    for(int i=0; i<lat_bounds.size(); i++)
    {
        vector<double> fetched;
        fetched=FetchLatOrLong(latlongs, lat_bounds[i], 1);
        border_points.push_back(fetched);
    }

    for(int i=0; i<long_bounds.size(); i++)
    {
        vector<double> fetched;
        fetched=FetchLatOrLong(latlongs, long_bounds[i], 0);
        border_points.push_back(fetched);
    }

    /*for(int i=0; i<border_points.size(); i++)
    {
        cout<<fixed<<setprecision(0)<<border_points[i][2]<<", ";
        cout<<setprecision(6)<<border_points[i][0]<<", "<<border_points[i][1]<<" "<<"\n";
    }*/

    double nearest_distance= sqrt ( pow((border_points[0][0]- key[0]),2) + pow((border_points[0][1]- key[1]),2) );
    int counter=0;
    for(int i=1; i<border_points.size(); i++)
    {
        double temp= sqrt ( pow((border_points[i][0]- key[0]),2) + pow((border_points[i][1]- key[1]),2) );
        if(temp <= nearest_distance)
        {
            nearest_distance=temp;
            counter=i;
        }         
    }

    double radius=nearest_distance;
    counter=0;

    for(int i=0; i<latlongs.size(); i++)
    {
        if( (abs(latlongs[i][0]-key[0]) <= radius) || (abs(latlongs[i][1]-key[1]) <= radius) )
        {
            double temp = sqrt ( pow((latlongs[i][0] - key[0]),2) + pow((latlongs[i][1] - key[1]),2) );
            if(temp <= nearest_distance)
            {
                nearest_distance=temp;
                counter=i;
            }
        }
    }

    return latlongs[counter];
}

vector<double> FetchLatOrLong(vector<vector<double> > latlongs, double lat_or_long, int lat_flag)
{
    if(lat_flag==1)
    {
        for(int i=0; i<latlongs.size(); i++)
        {
            if(lat_or_long==latlongs[i][0])
            {
                vector<double> temp;
                temp.push_back(latlongs[i][0]);
                temp.push_back(latlongs[i][1]);
                temp.push_back(latlongs[i][2]);
                return temp;
            }
        }
        return {-1,-1,-1};
    }
    else
    {
        for(int i=0; i<latlongs.size(); i++)
        {
            if(lat_or_long==latlongs[i][1])
            {
                vector<double> temp;
                temp.push_back(latlongs[i][0]);
                temp.push_back(latlongs[i][1]);
                temp.push_back(latlongs[i][2]);
                return temp;
            }
        }
        return {-1,-1,-1};
    }
}

vector<double> FetchRSP(double cc, string filename)
{
    ifstream rsp;
    vector<double> result;
    rsp.open(filename.c_str(), ios::in);
    string line, word;

    while (getline(rsp,line))
    {
        stringstream ss(line);
        vector<double> row;

        //Splitting with delimiter as comma
        while (getline(ss, word, ','))
        {
            row.push_back(atof(word.c_str()));
        }
        if(row[5]==cc)
            result.push_back(row[12]);
    }

    return result;    
}
