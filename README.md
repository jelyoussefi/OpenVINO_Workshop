  
# Intel® OpenVINO™ Toolkit (Windows)
In this tutorial you will build and run some of samples applications which come with the Intel® OpenVINO™ Toolkit and an Intel® pretrained model. Once completed you will have an understanding of the code required to start creating your own OpenVINO™ based solutions and how to target various accelerators in the Intel® portfolio (CPU, GPU, VPU).

## System Requirements
* Operating Systems

	* Microsoft Windows* 10 64-bit

## Prerequisites
* [Install Intel® Distribution of OpenVINO™ toolkit for Windows* 10](https://software.intel.com/en-us/articles/OpenVINO-Install-Windows)




# Building the Sample Applications on Windows* OS

Follow these steps to prepare your Windows computer for the samples:

- Go to the **<INSTALL_DIR>\deployment_tools\inference_engine\samples\** directory.
- Double-click **create_msvc<version>_solution.bat**, where <version> is 2015 or 2017 to match your Visual Studio version. For example, for Microsoft Visual Stuio 2017: **create_msvc2017_solution.bat**. This file generates Microsoft Visual Studio solution.
Open Microsoft Visual Studio*.
- Build **C:\Users\<username>\Documents\Intel\OpenVINO\inference_engine_samples_<version>\Samples.sln**, where <version> is 2015 or 2017 depending on your Visual Studio version.
- The sample application binaries are in the **C:\Users\<username>\Documents\Intel\OpenVINO** directory.


## Conclusion
In this tutorial we have created a simple application which is able to detect faces in a live camera stream using the Intel® OpenVINO™ Toolkit and an SSD pretrained model. We looked at the basic OpenVINO™ workflow and used the Inference Engine API to add basic face detection functionality to our application. We then looked at ways of improving performance by taking advantage of asynchronous calls in the Inference Engine API before exploring the ease of which the same code can be run on various different hardware in the Intel® portfolio such as GPUs and Intel® Myriad™ VPUs.

## Next Steps
A number of Inference Engine samples are included with OpenVINO™ which allow you to explore it's capabilities using pretrained models. The sample executables can be found in the following directory:

> Documents\Intel\OpenVINO\inference_engine_samples_2015\intel64\Release

You can find additional information about the samples with examples of how to use them [HERE](https://software.intel.com/en-us/articles/OpenVINO-IE-Samples).

## Additional Resources
[Intel® OpenVINO™ Toolkit](https://software.intel.com/en-us/openvino-toolkit)

[Inference Engine Developer Guide](https://software.intel.com/en-us/articles/OpenVINO-InferEngine)

[Pretrained Models](https://software.intel.com/en-us/openvino-toolkit/documentation/pretrained-models)
