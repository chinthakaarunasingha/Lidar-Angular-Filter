#include <ros/ros.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/point_types.h>
#include <pcl/PCLPointCloud2.h>
#include <pcl/conversions.h>
#include <pcl_ros/transforms.h>


class SubscribeAndPublish
{
public:
	SubscribeAndPublish()
	{

		sub_ = n_.subscribe<sensor_msgs::PointCloud2>("/cropbox/output",1,&SubscribeAndPublish::cloud_cb,this);
		pub_ = n_.advertise<pcl::PCLPointCloud2>("/converted",1);
		
	}

void cloud_cb(const boost::shared_ptr<const sensor_msgs::PointCloud2>& input){

    pcl::PCLPointCloud2 pcl_pc2;
    pcl_conversions::toPCL(*input,pcl_pc2);
    pcl::PointCloud<pcl::PointXYZ>::Ptr temp_cloud(new pcl::PointCloud<pcl::PointXYZ>);
    pcl::fromPCLPointCloud2(pcl_pc2,*temp_cloud);
    //do stuff with temp_cloud here
    pub_.publish(*temp_cloud);
    }

private:
  ros::NodeHandle n_; 
  ros::Publisher pub_;
  ros::Subscriber sub_;

};
int main(int argv, char** argc)
{
	ros::init(argv,argc,"convert");
	SubscribeAndPublish SAPObject;
	ros::spin();

	return 0;
}

