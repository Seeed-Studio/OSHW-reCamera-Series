import { useEffect, useState, useRef } from "react";
import { ServiceStatus } from "@/enum";
import { Progress, Alert } from "antd";
import { queryServiceStatusApi } from "@/api/device";
import gif from "@/assets/gif/loading.gif";

const totalDuration = 100 * 1000; // 100秒

const Loading = ({
  onServiceStatusChange,
}: {
  onServiceStatusChange?: (serviceStatus: ServiceStatus) => void;
}) => {
  const [serviceStatus, setServiceStatus] = useState<ServiceStatus>(
    ServiceStatus.STARTING
  );
  const serviceStatusRef = useRef(ServiceStatus.STARTING);
  const [progress, setProgress] = useState(0);
  const tryCount = useRef<number>(0);

  useEffect(() => {
    onServiceStatusChange?.(serviceStatus);
  }, [serviceStatus]);

  useEffect(() => {
    queryServiceStatus();
  }, []);

  const queryServiceStatus = async () => {
    tryCount.current = 0;
    setServiceStatus(ServiceStatus.STARTING);
    serviceStatusRef.current = ServiceStatus.STARTING;

    while (tryCount.current < 30) {
      try {
        const response = await queryServiceStatusApi();
        if (response.code === 0 && response.data) {
          const { sscmaNode, nodeRed, system, uptime = 0 } = response.data;
          if (
            sscmaNode === ServiceStatus.RUNNING &&
            nodeRed === ServiceStatus.RUNNING &&
            system === ServiceStatus.RUNNING
          ) {
            setProgress(100);
            if (tryCount.current == 0) {
              setServiceStatus(ServiceStatus.RUNNING);
              serviceStatusRef.current = ServiceStatus.RUNNING;
            } else {
              setTimeout(() => {
                setServiceStatus(ServiceStatus.RUNNING);
                serviceStatusRef.current = ServiceStatus.RUNNING;
              }, 1000);
            }
            return;
          } else {
            let percentage = (uptime / totalDuration) * 100;
            percentage = percentage >= 100 ? 99.99 : percentage;
            setProgress(parseFloat(percentage.toFixed(2)));
          }
        }
        tryCount.current++;
        setServiceStatus(ServiceStatus.STARTING);
        serviceStatusRef.current = ServiceStatus.STARTING;
        await new Promise((resolve) => setTimeout(resolve, 5000));
      } catch (error) {
        tryCount.current++;
        console.error("Error querying service status:", error);
      }
    }
    setServiceStatus(ServiceStatus.FAILED);
    serviceStatusRef.current = ServiceStatus.FAILED;
  };

  return (
    <div className="flex justify-center items-center absolute left-0 top-0 right-0 bottom-0 z-100 bg-[#f1f3f5]">
      {serviceStatus == ServiceStatus.STARTING && (
        <div className="w-1/2">
          <img className="w-full" src={gif} />
          {progress > 0 && (
            <Progress
              className="p-12 mt-36"
              percent={progress}
              strokeColor={"#8FC31F"}
            />
          )}
          <div className="text-16 mx-12 text-center">
            Please wait for node-red service to get start, it takes around 1 and
            an half minutes.
          </div>
        </div>
      )}
      {serviceStatus == ServiceStatus.FAILED && (
        <div className="w-1/2">
          <Alert
            message="System Error"
            description={
              <span>
                Looks like something went wrong with system. Please check system
                and restart, or contact{" "}
                <a
                  href="mailto:techsupport@seeed.io"
                  style={{ color: "#4096ff" }}
                >
                  techsupport@seeed.io
                </a>{" "}
                for support.
              </span>
            }
            type="error"
            showIcon
          />
        </div>
      )}
    </div>
  );
};

export default Loading;
