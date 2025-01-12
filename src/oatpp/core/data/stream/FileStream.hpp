/***************************************************************************
 *
 * Project         _____    __   ____   _      _
 *                (  _  )  /__\ (_  _)_| |_  _| |_
 *                 )(_)(  /(__)\  )( (_   _)(_   _)
 *                (_____)(__)(__)(__)  |_|    |_|
 *
 *
 * Copyright 2018-present, Leonid Stryzhevskyi <lganzzzo@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 ***************************************************************************/

#ifndef oatpp_data_stream_FileStream_hpp
#define oatpp_data_stream_FileStream_hpp

#include "Stream.hpp"

#include <cstdio>

namespace oatpp { namespace data{ namespace stream {

/**
 * Wrapper over `std::FILE`.
 */
class FileInputStream : public InputStream {
private:
  std::FILE* m_file;
  bool m_ownsFile;
  IOMode m_ioMode;
public:

  /**
   * Constructor.
   * @param file - file.
   * @param ownsFile - if `true` then call close on `FileInputStream` destruction.
   */
  FileInputStream(std::FILE* file, bool ownsFile);

  /**
   * Constructor.
   * @param filename - name of the file.
   */
  FileInputStream(const char* filename);

  /**
   * Virtual destructor.
   */
  ~FileInputStream();

  /**
   * Get file.
   * @return
   */
  std::FILE* getFile();

  /**
   * Read data from stream up to count bytes, and return number of bytes actually read. <br>
   * It is a legal case if return result < count. Caller should handle this!
   * @param data - buffer to read data to.
   * @param count - size of the buffer.
   * @return - actual number of bytes read.
   */
  data::v_io_size read(void *data, v_buff_size count) override;

  /**
   * Implementation of InputStream must suggest async actions for I/O results. <br>
   * Suggested Action is used for scheduling coroutines in async::Executor. <br>
   * **Stream MUST always give the same file-handle if applicable**
   * @param ioResult - result of the call to &l:InputStream::read ();.
   * @return - &id:oatpp::async::Action;.
   */
  oatpp::async::Action suggestInputStreamAction(data::v_io_size ioResult) override;

  /**
   * Set stream I/O mode.
   * @throws
   */
  void setInputStreamIOMode(IOMode ioMode) override;

  /**
   * Get stream I/O mode.
   * @return
   */
  IOMode getInputStreamIOMode() override;

};

/**
 * Wrapper over `std::FILE`.
 */
class FileOutputStream : public OutputStream {
private:
  std::FILE* m_file;
  bool m_ownsFile;
  IOMode m_ioMode;
public:

  /**
   * Constructor.
   * @param file - file.
   * @param ownsFile - if `true` then call close on `FileInputStream` destruction.
   */
  FileOutputStream(std::FILE* file, bool ownsFile);

  /**
   * Constructor.
   * @param filename - name of the file.
   * @param mode - ("wb" - create new/override, "ab" - create new/append).
   */
  FileOutputStream(const char* filename, const char* mode = "wb");

  /**
   * Virtual destructor.
   */
  ~FileOutputStream();

  /**
   * Get file.
   * @return
   */
  std::FILE* getFile();

  /**
   * Write data to stream up to count bytes, and return number of bytes actually written. <br>
   * It is a legal case if return result < count. Caller should handle this!
   * @param data - data to write.
   * @param count - number of bytes to write.
   * @return - actual number of bytes written. &id:oatpp::data::v_io_size;.
   */
  data::v_io_size write(const void *data, v_buff_size count) override;

  /**
   * Implementation of OutputStream must suggest async actions for I/O results. <br>
   * Suggested Action is used for scheduling coroutines in async::Executor. <br>
   * **Stream MUST always give the same file-handle if applicable**
   * @param ioResult - result of the call to &l:OutputStream::write ();.
   * @return - &id:oatpp::async::Action;.
   */
  oatpp::async::Action suggestOutputStreamAction(data::v_io_size ioResult) override;

  /**
   * Set stream I/O mode.
   * @throws
   */
  void setOutputStreamIOMode(IOMode ioMode) override;

  /**
   * Get stream I/O mode.
   * @return
   */
  IOMode getOutputStreamIOMode() override;

};

}}}

#endif // oatpp_data_stream_FileStream_hpp
