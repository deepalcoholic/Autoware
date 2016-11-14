/*
 * DataRW.h
 *
 *  Created on: Jun 23, 2016
 *      Author: hatem
 */

#ifndef DATARW_H_
#define DATARW_H_

#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>

namespace UtilityHNS {

class DataRW
{
public:
	DataRW();
	virtual ~DataRW();

	static std::string LoggingMainfolderName;
	static std::string ControlLogFolderName;
	static std::string PathLogFolderName;
	static std::string StatesLogFolderName;
	static std::string SimulationFolderName;
	static std::string KmlMapsFolderName;
	static std::string VectorMapsFolderName;

	static void WriteKMLFile(const std::string& fileName, const std::vector<std::string>& gps_list);
	static void WriteKMLFile(const std::string& fileName, const std::vector<std::vector<std::string> >& gps_list);
	static void WriteLogData(const std::string& logFolder, const std::string& logTitle, const std::string& header, const std::vector<std::string>& logData);
};

class SimpleReaderBase
{
private:
	std::ifstream* m_pFile;
	std::vector<std::string> m_RawHeaders;
	std::vector<std::string> m_DataTitlesHeader;
	std::vector<std::vector<std::vector<std::string> > > m_AllData;
	int m_nHeders;
	int m_iDataTitles;
	int m_nVarPerObj;
	int m_nLineHeaders;
	std::string m_HeaderRepeatKey;

	void ReadHeaders();
	void ParseDataTitles(const std::string& header);

public:
	/**
	 *
	 * @param fileName log file name
	 * @param nHeaders number of data headers
	 * @param iDataTitles which row contains the data titles
	 * @param nVariablesForOneObject 0 means each row represents one object
	 */
	SimpleReaderBase(const std::string& fileName, const int& nHeaders = 2,
			const int& iDataTitles = 1, const int& nVariablesForOneObject = 0,
			const int& nLineHeaders = 0, const std::string& headerRepeatKey = "...");
	~SimpleReaderBase();

protected:
	bool ReadAllData();
	bool ReadSingleLine(std::vector<std::vector<std::string> >& line);

};

//class GPSLocalizerReader : public SimpleReaderBase
//{
//	public:
//		GPSLocalizerReader(const std::string& fileName) : SimpleReaderBase(fileName){}
//		~GPSLocalizerReader(){}
//
//		bool ReadNextLine( MsgEstPose& pos, double& logTime);
//		void ReadAllData(vector<pair<double,  MsgEstPose> >& pos_list);
//};
//
//class GPSDataReader : public SimpleReaderBase
//{
//	public:
//	GPSDataReader(const string& fileName) : SimpleReaderBase(fileName){}
//	~GPSDataReader(){}
//
//	bool ReadNextLine( MsgGPSStandard& pos, double& logTime);
//	void ReadAllData(vector<pair<double,  MsgGPSStandard> >& pos_list);
//};
//
//class VehicleStateReader : public SimpleReaderBase
//{
//	public:
//	VehicleStateReader(const string& fileName) : SimpleReaderBase(fileName){}
//	~VehicleStateReader(){}
//
//	bool ReadNextLine( MsgVehicleStatus& state, double& logTime);
//	void ReadAllData(vector<pair<double,  MsgVehicleStatus> >& state_list);
//};
//
//class MovingObjectsReader : public SimpleReaderBase
//{
//	public:
//	MovingObjectsReader(const string& fileName) : SimpleReaderBase(fileName, 2, 1, 28, 4){}
//	~MovingObjectsReader(){}
//
//	bool ReadNextLine( MsgMovingObject& state, double& logTime);
//	void ReadAllData(vector<pair<double,  MsgMovingObject> >& state_list);
//};

class SimulationFileReader : public SimpleReaderBase
{
public:
	struct SimulationPoint
	{
		double x;
		double y;
		double z;
		double a;
		double c;
		double v;
	};

	struct SimulationData
	{
		SimulationPoint startPoint;
		SimulationPoint goalPoint;
		std::vector<SimulationPoint> simuCars;
	};

	SimulationFileReader(const std::string& fileName) : SimpleReaderBase(fileName, 1){}
	~SimulationFileReader(){}

	bool ReadNextLine(SimulationPoint& data);
	void ReadAllData(SimulationData& data_list);
};

class LocalizationPathReader : public SimpleReaderBase
{
public:
	struct LocalizationWayPoint
	{
		double x;
		double y;
		double z;
		double a;
		double v;
	};

	LocalizationPathReader(const std::string& fileName) : SimpleReaderBase(fileName, 1){}
	~LocalizationPathReader(){}

	bool ReadNextLine(LocalizationWayPoint& data);
	void ReadAllData(std::vector<LocalizationWayPoint>& data_list);
};

class AisanPointsFileReader : public SimpleReaderBase
{
public:
	struct AisanPoints
	{
		int PID;
		double B;
		double L;
		double H;
		double Bx;
		double Ly;
		int Ref;
		int MCODE1;
		int MCODE2;
		int MCODE3;
	};

	AisanPointsFileReader(const std::string& fileName) : SimpleReaderBase(fileName, 1){}
	~AisanPointsFileReader(){}

	bool ReadNextLine(AisanPoints& data);
	void ReadAllData(std::vector<AisanPoints>& data_list);
};

class AisanNodesFileReader : public SimpleReaderBase
{
public:

	struct AisanNode
	{
		int NID;
		int PID;
	};

	AisanNodesFileReader(const std::string& fileName) : SimpleReaderBase(fileName, 1){}
	~AisanNodesFileReader(){}

	bool ReadNextLine(AisanNode& data);
	void ReadAllData(std::vector<AisanNode>& data_list);
};

class AisanLinesFileReader : public SimpleReaderBase
{
public:

	struct AisanLine
	{
		int LID;
		int BPID;
		int FPID;
		int BLID;
		int FLID;
	};

	AisanLinesFileReader(const std::string& fileName) : SimpleReaderBase(fileName, 1){}
	~AisanLinesFileReader(){}

	bool ReadNextLine(AisanLine& data);
	void ReadAllData(std::vector<AisanLine>& data_list);
};

class AisanCenterLinesFileReader : public SimpleReaderBase
{
public:

	struct AisanCenterLine
	{
		int 	DID;
		int 	Dist;
		int 	PID;
		double 	Dir;
		double 	Apara;
		double 	r;
		double 	slope;
		double 	cant;
		double 	LW;
		double 	RW;
	};

	AisanCenterLinesFileReader(const std::string& fileName) : SimpleReaderBase(fileName, 1){}
	~AisanCenterLinesFileReader(){}

	bool ReadNextLine(AisanCenterLine& data);
	void ReadAllData(std::vector<AisanCenterLine>& data_list);
};

class AisanLanesFileReader : public SimpleReaderBase
{
public:

	struct AisanLane
	{
		int LnID	;
		int DID		;
		int BLID	;
		int FLID	;
		int BNID	;
		int FNID	;
		int JCT		;
		int BLID2	;
		int BLID3	;
		int BLID4	;
		int FLID2	;
		int FLID3	;
		int FLID4	;
		int ClossID	;
		double Span	;
		int LCnt	;
		int Lno		;
		int LaneType;
		int LimitVel;
		int RefVel	;
		int RoadSecID;
		int LaneChgFG;
		int LinkWAID;
		char LaneDir;
		int  LeftLaneId;
		int RightLaneId;

	};

	AisanLanesFileReader(const std::string& fileName) : SimpleReaderBase(fileName, 1){}
	~AisanLanesFileReader(){}

	bool ReadNextLine(AisanLane& data);
	void ReadAllData(std::vector<AisanLane>& data_list);
};

} /* namespace UtilityHNS */

#endif /* DATARW_H_ */