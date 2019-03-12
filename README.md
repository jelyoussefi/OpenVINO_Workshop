  
# Intel® OpenVINO™ Toolkit (Windows)
In this tutorial you will build and run some of samples applications which come with the Intel® OpenVINO™ Toolkit and an Intel® pretrained model. Once completed you will have an understanding of the code required to start creating your own OpenVINO™ based solutions and how to target various accelerators in the Intel® portfolio (CPU, GPU, VPU).

## System Requirements
* Operating Systems

	* Microsoft Windows* 10 64-bit

## Prerequisites
* [Install Intel® Distribution of OpenVINO™ toolkit for Windows* 10](https://software.intel.com/en-us/articles/OpenVINO-Install-Windows)




# Building the Sample Applications on Windows* OS

The sample applications are provided as a CMake project so the first step is to use a CMake generator to generate our Visual Studio Solution so we can use the Visual Studio IDE for developing and debugging the code.

Follow these steps to prepare your Windows computer for the samples:

- Go to the **"C:\Intel\computer_vision_sdk\deployment_tools\inference_engine\samples\"** directory.

- Double-click **"create_msvc\<version\>_solution.bat"**, where <version> is 2015 or 2017 to match your Visual Studio version. For example, for Microsoft Visual Stuio 2017: **create_msvc2017_solution.bat**. This file generates Microsoft Visual Studio solution.

- **Double-click** the **"C:\Users\\<username\>\Documents\Intel\OpenVINO\inference_engine_samples_\<version\>\Samples.sln"** file which you just generated , where <version> is 2015 or 2017 depending on your Visual Studio version.

- Build the solution: **Build->Build Solution**

- Make sure the application built successfully by checking the **Output** log in the bottom left pane.

- The sample application binaries are in the **"C:\Users\<username>\Documents\Intel\OpenVINO"** directory.

## Running the Samples

### Image Classification Sample
#### Description

    This topic demonstrates how to run the Image Classification sample application, which does inference using image classification networks like AlexNet* and GoogLeNet*.

#### How It Works

    Upon the start-up, the sample application reads command-line parameters and loads a network and an image to the Inference Engine plugin. When inference is done, the application creates an output image and outputs data to the standard output stream.

#### Downloading and Optimizing the model (squeezenet)

- Open a command line

```console
c:\Intel\computer_vision_sdk\deployment_tools\model_downloader\downloader.py --name squeezenet1.1 --output_dir  models

c:\Intel\computer_vision_sdk\deployment_tools\model_optimizer\mo.py --input_model models\classification\squeezenet\1.1\caffe\squeezenet1.1.caffemodel --output_dir models\ir\FP32
```
#### Running


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



