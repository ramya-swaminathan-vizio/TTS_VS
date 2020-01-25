/**
 * @note Copyright (c) 2010 Trident Microsystems, Inc.
 *       All rights reserved
 *       The content of this file or document is CONFIDENTIAL and PROPRIETARY
 *       to Trident Microsystems, Inc. It is subject to the terms of a
 *       License Agreement between Licensee and Trident Microsystems, Inc.
 *       restricting among other things, the use, reproduction, distribution
 *       and transfer. Each of the embodiments, including this information and
 *       any derivative work shall retain this copyright notice.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file tplf_tts.h
 *
 * @brief this file define the tts header file for trident platform apis.
 *
 * @author
 *
 **/

/** @defgroup tplf_tts tplf_tts: Platform TTS Control Interface
  * @ingroup tplf */

#ifndef __TPLF_TTS_H__
#define __TPLF_TTS_H__
#if defined __cplusplus || defined __cplusplus__
extern "C" {
#endif

#include "trid_sysdef.h"
#include "trid_errno.h"
#include "trid_util.h"
#include "tplf_pri.h"
#include "tapi_tts.h"

/**
 * @ingroup tplf_tts
 * @brief Init IPC of tts module
 *
 * @param argc [in] the program argc
 * @param argv [in] the program argv
 *
 * @return SYS_NOERROR when Ok, SYS_FAILED when failed
 */
RETURN_TYPE Tplf_TTS_Init(int argc, char* argv[]) __WEAK__;

/**
 * @ingroup tplf_tts
 * @brief Deinit the IPC of tts module
 *
 * @return SYS_NOERROR when Ok, SYS_FAILED when failed
 */
RETURN_TYPE Tplf_TTS_Exit(void) __WEAK__;

/**
 * @ingroup tplf_tts
 * @brief TTS main function, you can use this function to say, set voice parameters, etc
 *
 * @param appid [in] Specify the application's resource ID.
 * @param func [in] the function id, see TtsFuncID
 * @param param [in][out] the paramter of the function
 * @param size [in] the parameter size
 *
 * @retval SYS_NOERROR   no error
 * @retval SYS_FAILED    error happened
 */
RETURN_TYPE Tplf_TTS_Call(trid_sint32 appid, TtsFuncID func, void* param, int size) __WEAK__;

/**
 * @ingroup tplf_tts
 * @brief Install the tts callback
 *
 * @param appId [in] Specify the application's resource ID.
 * @param cb [in] the callback function
 * @param param [in] Not used now
 *
 * @return SYS_NOERROR when Ok, SYS_FAILED when failed
 */
RETURN_TYPE Tplf_TTS_InstallCallback(trid_sint32 appId, TapiTtsCallbackFunc cb, void* param) __WEAK__;

/**
 * @ingroup tplf_tts
 * @brief Uninstall callback
 *
 * @param appId [in] Specify the application's resource ID.
 *
 * @return SYS_NOERROR when Ok, SYS_FAILED when failed
 */
RETURN_TYPE Tplf_TTS_UninstallCallback(trid_sint32 appId) __WEAK__;

#if defined __cplusplus || defined __cplusplus__
}
#endif

#endif
