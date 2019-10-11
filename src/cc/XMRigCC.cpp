/* XMRigCC
 * Copyright 2017-     BenDr0id    <https://github.com/BenDr0id>, <ben@graef.in>
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include <memory>

#include "base/io/log/backends/ConsoleLog.h"
#include "base/io/log/backends/FileLog.h"
#include "base/io/log/Log.h"
#include "Config.h"
#include "Httpd.h"

std::shared_ptr<Config> m_config;
std::shared_ptr<Httpd> m_httpd;

int main(int argc, char** argv)
{
  m_config = std::make_shared<Config>();

  xmrig::Log::add(new xmrig::ConsoleLog());
  if (m_config->logFile)
  {
    xmrig::Log::add(new xmrig::FileLog(m_config->logFileName.c_str()));
  }

  std::thread([]()
  {
    uv_run(uv_default_loop(), UV_RUN_DEFAULT);
    uv_loop_close(uv_default_loop());
  }).detach();

  m_httpd = std::make_shared<Httpd>(m_config);
  m_httpd->start();

  return 0;
}
